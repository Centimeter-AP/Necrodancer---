#include "pch.h"
#include "CWaterTile.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CBeatMgr.h"
#include "CSoundMgr.h"

CWaterTile::CWaterTile()
{
}

CWaterTile::~CWaterTile()
{
}

void CWaterTile::Initialize()
{
    m_tInfo.fCX = TILECX;
    m_tInfo.fCY = TILECY;
    m_pImgKey = L"WaterTile";
    m_eRender = RENDER_BACKGROUND;
    m_iTileIdx = Find_MyTileIdx();

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Tile/Tile_Water.bmp", L"WaterTile");
}

int CWaterTile::Update()
{
    if (m_bDead)
    {
        return OBJ_DEAD;
    }

	for (auto& pTile : (*CTileMgr::Get_Instance()->Get_TileVec()))
	{
		if (pTile->Get_TileIdx() == m_iTileIdx)
		{
			m_iDrawID = static_cast<CTile*>(pTile)->Get_DrawID();
		}
	}
	if (BEATMGR->Get_ObjectAbleToMove() == true)
		Check_PlayerInWater();

	__super::Update_Rect();

    return OBJ_NOEVENT;
}

void CWaterTile::Late_Update()
{
}

void CWaterTile::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		TILECX,
		TILECY,
		hMemDC,
		52 * m_iDrawID + 2,
		2,
		SRCCOPY);
}

void CWaterTile::Release()
{
}

void CWaterTile::Check_PlayerInWater()
{
	if (static_cast<CPlayer*>(GET_PLAYER)->Get_HeadTileIdx() == m_iTileIdx)
	{
		if (static_cast<CPlayer*>(GET_PLAYER)->Get_InWater() == false)
		{
			static_cast<CPlayer*>(GET_PLAYER)->Set_InWater(true);
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"mov_water_in.ogg", SOUND_EFFECT, 0.4f);
		}
	}
	if (static_cast<CPlayer*>(GET_PLAYER)->Get_InWater() == true && GET_PLAYER->Get_TileIdx() == m_iTileIdx)
	{
		m_bDead = true;
		static_cast<CPlayer*>(GET_PLAYER)->Set_InWater(false);
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"mov_water_out.ogg", SOUND_EFFECT, 0.4f);
	}

}
