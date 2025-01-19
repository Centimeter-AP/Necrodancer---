#include "pch.h"
#include "CDummy.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "CObjMgr.h"
#include "CBeatMgr.h"
#include "CSoundMgr.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"


void CDummy::Initialize()
{
	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 48.f;
	m_fSpeed = 6.f;


	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster.bmp", L"Monster");
	m_pvecTile = CTileMgr::Get_Instance()->Get_TileVec();
	m_iHeadTileIdx = m_iTileIdx = Find_MyTileIdx();

	m_tInfo.fX = (*m_pvecTile)[m_iTileIdx]->Get_Info().fX;
	m_tInfo.fY = (*m_pvecTile)[m_iTileIdx]->Get_Info().fY - 24.f;
	m_pTarget = GET_PLAYER;
	m_eDir = DIR_UP;
	CTileMgr::Get_Instance()->Set_TileObject(m_iHeadTileIdx, TOBJ_ENTITY, this);

	m_pImgKey = L"Monster";
	m_fJumpPower = 9.5f;
	Get_TileX();
	Get_TileY();
	m_eRender = RENDER_GAMEOBJECT;
	m_iMaxHP = 6;
	m_iHP = 6;
}

int CDummy::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_iHP = m_iMaxHP;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CDummy::Late_Update()
{

}

void CDummy::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);


	//GdiTransparentBlt(hDC,			// 복사 받을 DC
	//    m_tRect.left + iScrollX,	// 복사 받을 위치 좌표 X, Y	
	//    m_tRect.top + iScrollY,
	//    (int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
	//    (int)m_tInfo.fCY,
	//    hMemDC,						// 복사할 이미지 DC	
	//    0,							// 비트맵 출력 시작 좌표(Left, top)
	//    0,
	//    (int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
	//    (int)m_tInfo.fCY,
	//    RGB(255, 255, 255));		// 제거할 색상
}

void CDummy::Release()
{
}

void CDummy::Play_HitSound()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_MONHIT1);
	CSoundMgr::Get_Instance()->PlaySound(L"en_minotaur_hit_01.wav", SOUND_MONHIT1, 0.2f);
}