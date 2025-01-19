#include "pch.h"
#include "CStoneWall.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"

CStoneWall::CStoneWall()
{
}

CStoneWall::~CStoneWall()
{
}

void CStoneWall::Initialize()
{

	// 벽 기둥 30px

	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 78.f;
	m_pImgKey = L"Wall";
	m_eRender = RENDER_GAMEOBJECT;

	m_enWallType = STONE_WALL;
	// 벽 별로 imgpos 설정
	m_iImgPosX = 1392;
	// 1776 보스
	m_iImgPosY = 0;

	m_iHP = 2;
	m_iPowerNeeded = POWER_TWO;
}

int CStoneWall::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_iTileIdx = Find_MyTileIdx();
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CStoneWall::Late_Update()
{

}

void CStoneWall::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Wall");

	BitBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top - 15 + iScrollY,
		TILECX,
		78,
		hMemDC,
		m_iImgPosX,
		m_iImgPosY,
		SRCCOPY);

}

void CStoneWall::Release()
{
}
