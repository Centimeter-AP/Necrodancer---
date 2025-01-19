#include "pch.h"
#include "CDoor.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"

void CDoor::Initialize()
{

	// 벽 기둥 30px

	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 78.f;
	m_pImgKey = L"Wall";
	m_eRender = RENDER_GAMEOBJECT;
	m_enWallType = DOOR_WALL;

	// 벽 별로 imgpos 설정
	m_iImgPosX = 576;
	// 624 세로
	m_iImgPosY = 576;

	m_iHP = 1;
	m_iPowerNeeded = NO_POWER;
}

int CDoor::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_iTileIdx = Find_MyTileIdx();
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CDoor::Late_Update()
{

}

void CDoor::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Wall");

	//BitBlt(hDC,
	//	m_tRect.left + iScrollX,
	//	m_tRect.top - 15 + iScrollY,
	//	TILECX,
	//	78,
	//	hMemDC,
	//	m_iImgPosX,
	//	m_iImgPosY,
	//	SRCCOPY);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top - 15 + iScrollY, // 그림자 좀만 밑으로 지게
		TILECX,
		78,
		hMemDC,
		m_iImgPosX,
		m_iImgPosY,
		TILECX,
		78,
		RGB(255, 0, 255));


}

void CDoor::Release()
{
}
