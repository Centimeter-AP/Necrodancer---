#include "pch.h"
#include "CDirtWall.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"

CDirtWall::CDirtWall()
{
}

CDirtWall::~CDirtWall()
{
}

void CDirtWall::Initialize()
{

	// 벽 기둥 30px

	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 78.f;
	m_pImgKey = L"Wall";
	m_eRender = RENDER_GAMEOBJECT;

	m_enWallType = DIRT_WALL;
	// 벽 별로 imgpos 설정
	m_iImgPosX = 0;
	// 1632 보스
	m_iImgPosY = 0;

	m_iHP = 1;
	m_iPowerNeeded = POWER_ONE;
}

int CDirtWall::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_iTileIdx = Find_MyTileIdx();

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CDirtWall::Late_Update()
{

}

void CDirtWall::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Wall");

	//Rectangle(hDC
	//	, m_tRect.left + iScrollX
	//	, m_tRect.top + iScrollY - 24
	//	, m_tRect.right + iScrollX
	//	, m_tRect.bottom + iScrollY - 24);

	//GdiTransparentBlt(hDC,			// 복사 받을 DC
	//	m_tRect.left + iScrollX,	// 복사 받을 위치 좌표 X, Y	
	//	m_tRect.top - 15 + iScrollY,
	//	TILECX,						// 복사 받을 이미지의 가로, 세로
	//	78,
	//	hMemDC,						// 복사할 이미지 DC	
	//	m_iImgPosX,			// 비트맵 출력 시작 좌표(Left, top)
	//	m_iImgPosY,					// 타일 크기가 상하좌우 2픽셀씩 더 있
	//	TILECX,						// 복사할 이미지의 가로, 세로
	//	78,
	//	RGB(255, 0, 255));			// 제거할 색상

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

void CDirtWall::Release()
{
}
