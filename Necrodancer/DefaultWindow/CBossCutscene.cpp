#include "pch.h"
#include "CBossCutscene.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CKeyMgr.h"

void CBossCutscene::Initialize()
{
	//m_pImgKey = L"bosscreen_coralriff";
	//m_iTileIdx = Find_MyTileIdx();
	m_iMovingOffsetTop = -501;
	m_iMovingOffsetMid = 800;
	m_iMovingOffsetBottom = 500;
	m_fSpeed = 30.f;
	m_eRender = RENDER_UI;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/UI/bosscreen_coralriff_topblade.bmp", L"topblade");
	//501 57
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/UI/bosscreen_coralriff.bmp", L"bosscreen_coralriff");
	// 800 353
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/UI/bosscreen_coralriff_bottomblade.bmp", L"bottomblade");
	//500 66 
}

int CBossCutscene::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

	if (m_bIsAppear)
	{
		if (m_bCanMoveTop)
		{
			m_iMovingOffsetTop += m_fSpeed;
			if (m_iMovingOffsetTop >= 0)
			{
				m_iMovingOffsetTop = 0;
				m_bCanMoveTop = false;
			}
		}
		if (m_bCanMoveMid)
		{
			m_iMovingOffsetMid -= m_fSpeed;
			if (m_iMovingOffsetMid <= 0)
			{
				m_iMovingOffsetMid = 0;
				m_bCanMoveBottom = true;
				m_bCanMoveMid = false;
			}
		}
		if (m_bCanMoveBottom)
		{
			m_iMovingOffsetBottom -= m_fSpeed;
			if (m_iMovingOffsetBottom <= 0)
			{
				m_iMovingOffsetBottom = 0;
				m_bCanMoveBottom = false;
				m_bIsAppear = false;

			}
		}
	}
	if (m_bIsAppear == false && m_bIsDisappear == false)
	{
		++m_iDisappearTimer;
	}

	if (m_bIsDisappear)
	{
		if (m_bCanMoveTop)
		{
			m_iMovingOffsetTop -= m_fSpeed;
		}
		if (m_bCanMoveMid)
		{
			m_iMovingOffsetMid += m_fSpeed;
			if (m_iMovingOffsetMid >= 800)
				m_bDead = true;
		}
		if (m_bCanMoveBottom)
		{
			m_iMovingOffsetBottom += m_fSpeed;
		}
	}

	if (m_iDisappearTimer > 70)
	{
		m_bIsAppear = false;
		m_bIsDisappear = true;
		m_bCanMoveTop = true;
		m_bCanMoveMid = true;
		m_bCanMoveBottom = true;
	}

	__super::Update_Rect();
    return OBJ_NOEVENT;
}

void CBossCutscene::Late_Update()
{
}

void CBossCutscene::Render(HDC hDC)
{
	HDC		hMemDCTop = CBmpMgr::Get_Instance()->Find_Image(L"topblade");
	HDC		hMemDCMid = CBmpMgr::Get_Instance()->Find_Image(L"bosscreen_coralriff");
	HDC		hMemDCBot = CBmpMgr::Get_Instance()->Find_Image(L"bottomblade");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// 501 57
	// 800 353
	// 500 66
	GdiTransparentBlt(hDC,
		0 + m_iMovingOffsetTop,
		80,
		501,
		57,
		hMemDCTop,
		0,
		0,
		501,
		57,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		0 + m_iMovingOffsetMid,
		430 - 353,
		800,
		353,
		hMemDCMid,
		0,
		0,
		800,
		353,
		RGB(255, 0, 255));
	
	GdiTransparentBlt(hDC,
		400 + m_iMovingOffsetBottom,
		515 - 70,
		500,
		66,
		hMemDCBot,
		0,
		0,
		500,
		66,
		RGB(255, 0, 255));
}

void CBossCutscene::Release()
{
}
