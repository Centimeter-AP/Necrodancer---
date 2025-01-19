#include "pch.h"
#include "CSoundMgr.h"


CSoundMgr* CSoundMgr::m_pInstance = nullptr;
CSoundMgr::CSoundMgr()
{
	m_pSystem = nullptr; 
}


CSoundMgr::~CSoundMgr()
{
	Release(); 
}

void CSoundMgr::Initialize()
{
	// 사운드를 담당하는 대표객체를 생성하는 함수
	UINT	uiVersion(0);
	FMOD_System_Create(&m_pSystem, 131609U);
	
	// 1. 시스템 포인터, 2. 사용할 가상채널 수 , 초기화 방식) 
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile(); 
}
void CSoundMgr::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear(); 

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}

void CSoundMgr::PlaySound(const TCHAR * pSoundKey, CHANNELID eID, float fVolume)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter; 

	// iter = find_if(m_mapSound.begin(), m_mapSound.end(), CTag_Finder(pSoundKey));
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), 
		[&](auto& iter)->bool 
	{
		return !lstrcmp(pSoundKey, iter.first);
	});
	
	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE; 

	if (FMOD_Channel_IsPlaying(m_pChannelArr[eID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, iter->second, FALSE, FALSE, &m_pChannelArr[eID]);
	}

	FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::PlayBGM(const TCHAR * pSoundKey, float fVolume, CHANNELID eID)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	// iter = find_if(m_mapSound.begin(), m_mapSound.end(), CTag_Finder(pSoundKey));
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)->bool
	{
		return !lstrcmp(pSoundKey, iter.first);
	});
	
	if (iter == m_mapSound.end())
		return;
	FMOD_System_PlaySound(m_pSystem, iter->second, NULL, 0, &m_pChannelArr[eID]);
	FMOD_Channel_SetMode(m_pChannelArr[eID], FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);
	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::StopSound(CHANNELID eID)
{
	FMOD_Channel_Stop(m_pChannelArr[eID]);
}

void CSoundMgr::StopAll()
{
	for (int i = 0 ; i < SOUND_END; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);
}

void CSoundMgr::ChangeChannelVolume(CHANNELID eID, float fVolume)
{
	float fCurVol(0.f);


	FMOD_Channel_GetVolume(m_pChannelArr[eID], &fCurVol);

	fCurVol += fVolume;
	FMOD_Channel_SetVolume(m_pChannelArr[eID], fCurVol);

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::SetChannelVolume(CHANNELID eID, float fVolume)
{
	FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::PlaySoundFaster(CHANNELID eID, float fFrequency)
{
	// DSP 생성 (Pitch Shifter)
	FMOD_DSP* dspPitchShift;
	FMOD_System_CreateDSPByType(m_pSystem, FMOD_DSP_TYPE_PITCHSHIFT, &dspPitchShift);
	
	
	// DSP 설정 - 피치를 유지하면서 배속 변경
	FMOD_DSP_SetParameterFloat(dspPitchShift, FMOD_DSP_PITCHSHIFT_PITCH, 1.0f); // 피치 1.0 (기본값)
	FMOD_Channel_AddDSP(m_pChannelArr[eID], 0, dspPitchShift);
	
	float originalFrequency(0.f);
	FMOD_Channel_GetFrequency(m_pChannelArr[eID], &originalFrequency);
	FMOD_Channel_SetFrequency(m_pChannelArr[eID], originalFrequency * fFrequency);


}

bool CSoundMgr::IsChannelPeakLevelAboveThreshold(CHANNELID eID)
{
    if (eID < 0 || eID >= SOUND_END)
        return false;

    FMOD_DSP* pDSP = NULL;
    FMOD_RESULT result = FMOD_Channel_GetDSP(m_pChannelArr[eID], FMOD_CHANNELCONTROL_DSP_HEAD, &pDSP);
    if (result != FMOD_OK || !pDSP)
        return false;

    // DSP 메터링 활성화
    result = FMOD_DSP_SetMeteringEnabled(pDSP, true, true);
    if (result != FMOD_OK)
        return false;

    // FMOD 시스템 업데이트
    FMOD_System_Update(m_pSystem);

	FMOD_DSP_METERING_INFO meteringInfo{ 0 };
	FMOD_DSP_METERING_INFO inputMeteringInfo{ 0 };
    result = FMOD_DSP_GetMeteringInfo(pDSP, &inputMeteringInfo, &meteringInfo);
    if (result != FMOD_OK)
        return false;
	FMOD_DEBUG_FLAGS flags = FMOD_DEBUG_LEVEL_ERROR | FMOD_DEBUG_LEVEL_WARNING | FMOD_DEBUG_LEVEL_LOG;
	result = FMOD_Debug_Initialize(flags, FMOD_DEBUG_MODE_TTY, NULL, nullptr);
    // 메터링 정보 확인
    for (int i = 0; i < meteringInfo.numchannels; ++i)
    {	
		int temp = 20 * log(meteringInfo.peaklevel[i]);
        if (20 * log(meteringInfo.peaklevel[i]) > -50)
            return true;
    }

    return false;
}

//{
//	if (eID < 0 || eID >= SOUND_END)
//		return false;
//
//	FMOD_DSP* pDSP = NULL;
//	FMOD_RESULT result = FMOD_Channel_GetDSP(m_pChannelArr[eID], FMOD_CHANNELCONTROL_DSP_HEAD, &pDSP);
//	if (!pDSP)
//		return false;
//
//	FMOD_DSP_METERING_INFO meteringInfo;
//	FMOD_DSP_METERING_INFO inputmeteringInfo;
//	FMOD_DSP_SetMeteringEnabled(pDSP, true, true);
//	FMOD_DSP_GetMeteringInfo(pDSP, &inputmeteringInfo, &meteringInfo);
//
//	if (meteringInfo.peaklevel[0] > -20)
//		return true;
//
//	return false;
//}

void CSoundMgr::LoadSoundFile()
{
	// _finddata_t : <io.h>에서 제공하며 파일 정보를 저장하는 구조체
	_finddata_t fd; 

	// _findfirst : <io.h>에서 제공하며 사용자가 설정한 경로 내에서 가장 첫 번째 파일을 찾는 함수
	long long handle = _findfirst("../Sound/*.*", &fd);

	if (handle == -1)
		return; 

	int iResult = 0; 

	char szCurPath[128] = "../Sound/";	 // 상대 경로
	char szFullPath[128] = ""; 

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath); 
		
		// "../Sound/" + "Success.wav"
		strcat_s(szFullPath, fd.name);
		// "../Sound/Success.wav"

		FMOD_SOUND* pSound = nullptr; 

		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_DEFAULT, 0, &pSound);
	//	FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_LOOP_NORMAL, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = (int)strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);

			// 아스키 코드 문자열을 유니코드 문자열로 변환시켜주는 함수
			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}
		//_findnext : <io.h>에서 제공하며 다음 위치의 파일을 찾는 함수, 더이상 없다면 -1을 리턴
		iResult = _findnext(handle, &fd);
	}

	FMOD_System_Update(m_pSystem);

	_findclose(handle);
}

void CSoundMgr::PlaySound_DigVoice()
{
	TCHAR szKey[32];
	wsprintf(szKey, L"vo_cad_dig_0%d.wav", rand() % 4 + 1);
	CSoundMgr::Get_Instance()->StopSound(SOUND_VOCAL);
	CSoundMgr::Get_Instance()->PlaySound(szKey, SOUND_VOCAL, 0.35f);
}

void CSoundMgr::PlaySound_AttackVoice()
{
	TCHAR szKey[32];
	wsprintf(szKey, L"vo_cad_melee_1_0%d.wav", rand() % 4 + 1);
	CSoundMgr::Get_Instance()->StopSound(SOUND_VOCAL);
	CSoundMgr::Get_Instance()->PlaySound(szKey, SOUND_VOCAL, 0.35f);
}
