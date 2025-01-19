#include "pch.h"
#include "CBedrock.h"
#include "CScrollMgr.h"
#include "CSceneMgr.h"
#include "CBmpMgr.h"

CBedrock::CBedrock()
{
}

CBedrock::~CBedrock()
{
}

void CBedrock::Initialize()
{

	// 벽 기둥 30px

	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 78.f;
	m_pImgKey = L"Wall";
	m_eRender = RENDER_GAMEOBJECT;
	m_enWallType = BEDROCK;

	// 벽 별로 imgpos 설정
	m_iImgPosX = 192;
	m_iImgPosY = 576;


	m_iHP = 999;
	m_iPowerNeeded = POWER_NOEXCEPTION;
}

int CBedrock::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_BOSS)
	{
		m_iImgPosX = 1824;
		m_iImgPosY = 0;
	}
	m_iTileIdx = Find_MyTileIdx();
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBedrock::Late_Update()
{

}

void CBedrock::Render(HDC hDC)
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

void CBedrock::Release()
{
}
