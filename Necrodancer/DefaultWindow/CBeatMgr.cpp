#include "pch.h"
#include "CBeatMgr.h"
#include "Define.h"
#include "CObj.h"
#include "CSceneMgr.h"
#include "CSoundMgr.h"

CBeatMgr* CBeatMgr::m_pInstance = nullptr;

using namespace std::chrono;

CBeatMgr::CBeatMgr()
	: m_ullTimeChecker(GetTickCount64()), m_ullTimeTicker(GetTickCount64())
	, m_bIsBeatMissed(false), m_bIsPlayerActed(false), m_bRightTimeBeat(false)
	, m_bAbleBeatInterval(false), m_iBeatGapFrameCount(0), m_fBeatJudgementPx(80.f)
	, m_bObjectAbleToMove(false), m_iBeatCombo(0), m_iBPM(0), m_iBPMSec(0)
	, m_llTimeChecker(0), m_bInputBeatMissed(false)
{
	m_tTimerRightTime = m_tBeatStart = system_clock::now();
	m_tMusicStart = m_tBeatStart = system_clock::now();
}

CBeatMgr::~CBeatMgr()
{
}

int CBeatMgr::Update()
{
	// 결국 박자는 시간체크 말고 노트충돌처리로..
	// ... 시간체크로?
	++m_iBeatGapFrameCount;
	m_llTimeChecker = duration_cast<microseconds>(system_clock::now() - m_tBeatStart);
	if (m_llTimeChecker.count() >= m_iBPMSec)
	{
		if (m_bRightTimeBeat == false)
		{
			m_tBeatStart += microseconds(m_iBPMSec);
			m_tTimerRightTime = system_clock::now();
			m_bRightTimeBeat = true;
			if (CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_BOSS)
				m_fBeatJudgementPx = (float)m_iBeatGapFrameCount * 0.5f * 4.f * (126.f / 115.f);
			else
				m_fBeatJudgementPx = (float)m_iBeatGapFrameCount * 0.5f * 4.f;

			m_iBeatGapFrameCount = 0;
		}
	}
	if (duration_cast<milliseconds>(system_clock::now() - m_tTimerRightTime).count() > 80)
	{
		m_bRightTimeBeat = false;
	}

	return 0;
}

void CBeatMgr::Late_Update()
{
	if(!m_BeatBarlist.empty())
	{
		if (m_BeatBarlist.front()->Get_Info().fX <= (float)WINCX * 0.5f + m_fBeatJudgementPx
			&& m_BeatBarlist.front()->Get_Info().fX >= (float)WINCX * 0.5f - m_fBeatJudgementPx)
		{
			m_bAbleBeatInterval = true;
		}
		else
		{
			m_bAbleBeatInterval = false;
		}
	}
}

void CBeatMgr::Render(HDC hDC)
{
	//m_bIsBeatMissed = false;
	m_bIsPlayerActed = false;
	
	//TCHAR szText[32];
	//wsprintf(szText, L"m_iBeatGapFrameCount : %d ", m_iBeatGapFrameCount);
	//TextOut(hDC, 0, 0, szText, lstrlen(szText));
}

void CBeatMgr::Release()
{
}

void CBeatMgr::Set_Bar(CObj* _Bar)
{
	m_BeatBarlist.push_back(_Bar);
}

void CBeatMgr::Delete_Bar(CObj* _pBar)
{
	if (!m_BeatBarlist.empty())
	{
		auto iter = m_BeatBarlist.begin();
		for (iter = m_BeatBarlist.begin(); iter != m_BeatBarlist.end(); ++iter)
		{
			if ((*iter) == _pBar)
			{
				break;
			}
		}
		if (iter == m_BeatBarlist.end())
			return;
		iter = m_BeatBarlist.erase(iter);
	}
}

void CBeatMgr::Delete_Bar_Act()
{
	 //입력 가능한 박자일 때만 삭제되게 조건 추가할 것 

	if (!m_BeatBarlist.empty())
	{
		m_BeatBarlist.front()->Set_Dead();
		m_BeatBarlist.pop_front();
		m_BeatBarlist.front()->Set_Dead();
		m_BeatBarlist.pop_front();
	}
	if (CBeatMgr::Get_Instance()->Get_BeatMissed() == true)
	{
		CBeatMgr::Get_Instance()->Set_BeatMissed(false);
	}
}

void CBeatMgr::Empty_Bar()
{

	for (auto iter = m_BeatBarlist.begin(); iter != m_BeatBarlist.end();)
	{
		(*iter)->Set_Dead();
		iter = m_BeatBarlist.erase(iter);
	}
}

void CBeatMgr::Plus_BeatCombo()
{
	if (m_iBeatCombo == 0)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT4);
		CSoundMgr::Get_Instance()->PlaySound(L"sfx_chain_groove_ST.ogg", SOUND_EFFECT4, 0.5f);
	}

	++m_iBeatCombo; 
	if (m_iBeatCombo > 3)
	{
		m_iBeatCombo = 3;
	}
}

void CBeatMgr::Lose_BeatCombo()
{
	if (m_iBeatCombo != 0)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT4);
		CSoundMgr::Get_Instance()->PlaySound(L"sfx_chain_break_ST.ogg", SOUND_EFFECT4, 0.5f);
	}
	m_iBeatCombo = 0;
}
