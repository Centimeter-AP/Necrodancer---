#include "pch.h"
#include "CHeartbeat.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CBeatMgr.h"
#include "CTileMgr.h"
#include "CObjMgr.h"
#include "Define.h"
#include "CAbstractFactory.h"
#include "CMissInputText.h"

void CHeartbeat::Initialize()
{
	m_tInfo = { (float)WINCX * 0.5f, (float)WINCY - 145.f, 80.f, 100.f };
    m_pImgKey = L"Heartbeat";

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/UI/Heartbeat.bmp", L"Heartbeat");
	m_eRender = RENDER_UI;
}

int CHeartbeat::Update()
{


	if (CBeatMgr::Get_Instance()->Get_RightTimeBeat())
	{
		if (m_iBeat == 0)
		{
			m_iBeat = 1;
		}
	}
	else
	{
		m_iBeat = 0;
	}

	if (BEATMGR->Get_InputBeatMissed() == true)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CMissInputText>::Create());
		BEATMGR->Set_InputBeatMissed(false);
	}


	__super::Update_Rect();
    return OBJ_NOEVENT;
}

void CHeartbeat::Late_Update()
{
}

void CHeartbeat::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC		hMemDCskiptext = CBmpMgr::Get_Instance()->Find_Image(L"beatskipped1");	// 그림자 용 xy 좌표 따로?

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Heartbeat");

	GdiTransparentBlt(hDC,					// 복사 받을 DC
		m_tRect.left,			// 복사 받을 위치 좌표 X, Y	
		m_tRect.top,
		(int)m_tInfo.fCX,							// 복사 받을 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		hMemDC,								// 복사할 이미지 DC	
		(int)m_tInfo.fCX * m_iBeat,	// 비트맵 출력 시작 좌표(Left, top)
		0,
		(int)m_tInfo.fCX,							// 복사할 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));					// 제거할 색상

	TCHAR szText[32];
	wsprintf(szText, L"콤보 배수 : %d배", CBeatMgr::Get_Instance()->Get_BeatCombo() + 1);
	TextOut(hDC, 
			WINCX / 2 - 55, 
			WINCY - 100,
			szText, lstrlen(szText));


	//if (CBeatMgr::Get_Instance()->Get_BeatMissed())
	//{

	//	GdiTransparentBlt(hDC,
	//		m_tRect.left,
	//		m_tRect.top,
	//		77,
	//		15,
	//		hMemDCskiptext,
	//		0,
	//		0,
	//		77,
	//		15,
	//		RGB(255, 0, 255));
	//}


}

void CHeartbeat::Release()
{
}
