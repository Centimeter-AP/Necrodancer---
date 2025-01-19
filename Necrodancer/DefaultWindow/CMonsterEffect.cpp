#include "pch.h"
#include "CMonsterEffect.h"
#include "Define.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"

void CMonsterEffect::Initialize()
{// 54, 48 
	m_tInfo.fCX = 54;
	m_tInfo.fCY = 48;
	m_pImgKey = L"MonsterEffectRL";
	//m_iTileIdx = Find_MyTileIdx();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Effect/swipe_enemy_RL.bmp", L"MonsterEffectRL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Effect/swipe_enemy_UD.bmp", L"MonsterEffectUD");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Effect/HitParticle.bmp", L"HitParticle");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 40;
	m_tFrame.dwTime = GetTickCount64();
	m_eRender = RENDER_EFFECT;
}

int CMonsterEffect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_eDir = m_pTarget->Get_Direction();

	switch (m_eDir)
	{
	case DIR_LEFT:
		m_pImgKey = L"MonsterEffectRL";
		m_tFrame.iMotion = 1;
		m_tInfo.fCX = 54;
		m_tInfo.fCY = 48;
		break;
	case DIR_RIGHT:
		m_pImgKey = L"MonsterEffectRL";
		m_tFrame.iMotion = 0;
		m_tInfo.fCX = 54;
		m_tInfo.fCY = 48;
		break;
	case DIR_UP:
		m_pImgKey = L"MonsterEffectUD";
		m_tFrame.iMotion = 1;
		m_tInfo.fCX = 48;
		m_tInfo.fCY = 54;
		break;
	case DIR_DOWN:
		m_pImgKey = L"MonsterEffectUD";
		m_tFrame.iMotion = 0;
		m_tInfo.fCX = 48;
		m_tInfo.fCY = 54;
		break;
	default:
		break;
	}

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CMonsterEffect::Late_Update()
{
	if (m_tFrame.iFrameStart == 5)
		m_bDead = true;
	__super::Move_Frame();
}

void CMonsterEffect::Render(HDC hDC)
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
		48,
		48,
		hMemDChit,
		48 * m_tFrame.iFrameStart,
		0,
		48,
		48,
		RGB(255, 0, 255));
	
}

void CMonsterEffect::Release()
{
}
