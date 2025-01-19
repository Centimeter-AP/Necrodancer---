#include "pch.h"
#include "CDaggerEffect.h"
#include "Define.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CObjMgr.h"

void CDaggerEffect::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
	m_pImgKey = L"DaggerEffect";
	//m_iTileIdx = Find_MyTileIdx();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Effect/swipe_dagger.bmp", L"DaggerEffect");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Effect/HitParticle.bmp", L"HitParticle");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3; 
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount64();
	m_pTarget = GET_PLAYER;
	m_eDir = m_pTarget->Get_Direction();
	m_eRender = RENDER_EFFECT;
}

int CDaggerEffect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_eDir = m_pTarget->Get_Direction();
	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tFrame.iMotion = 1;
		break;
	case DIR_RIGHT:
		m_tFrame.iMotion = 0;
		break;
	case DIR_UP:
		m_tFrame.iMotion = 2;
		break;
	case DIR_DOWN:
		m_tFrame.iMotion = 3;
		break;
	default:
		break;
	}

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CDaggerEffect::Late_Update()
{
	if (m_tFrame.iFrameStart == 3)
		m_bDead = true;
	__super::Move_Frame();
}

void CDaggerEffect::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));

	HDC		hMemDChit = CBmpMgr::Get_Instance()->Find_Image(L"HitParticle");
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top - 12 + iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDChit,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CDaggerEffect::Release()
{
}
