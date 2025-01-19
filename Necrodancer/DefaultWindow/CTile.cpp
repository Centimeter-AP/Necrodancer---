#include "pch.h"
#include "CTile.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CBeatMgr.h"

CTile::CTile() : m_iDrawID(0), m_iOption(0), m_pObject{0,}
{
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_pImgKey = L"Tile";
	m_eRender = RENDER_BACKGROUND;

}

int CTile::Update()
{
	m_iTileIdx = Find_MyTileIdx();
	if (CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_BOSS)
	{
		m_pImgKey = L"Tile_Boss";
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
	for (int i = 0; i < TOBJ_END; ++i)
	{
		if (m_pObject[i] != nullptr)
		{
			if (m_pObject[i]->Get_TileIdx() != this->Get_TileIdx())
			{
				m_pObject[i] = nullptr;
			}
		}
	}
}

void CTile::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	int		iBeatCorrect(0);
	iBeatCorrect = (CBeatMgr::Get_Instance()->Get_BeatCombo() ? 1 : 0);

	BitBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top  + iScrollY,
		TILECX,
		TILECY,
		hMemDC,
		52 * m_iDrawID + 2,
		52 * iBeatCorrect + 2 ,
		SRCCOPY);

}

void CTile::Release()
{
}
