#include "pch.h"
#include "CStair.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CSoundMgr.h"

void CStair::Initialize()
{
    m_tInfo.fCX = TILECX;
    m_tInfo.fCY = TILECY;
	m_pImgKey = L"Stair";
	m_eRender = RENDER_BACKGROUND;
    m_iTileIdx = Find_MyTileIdx();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Tile/Tile_Stair.bmp", L"Stair");

}

int CStair::Update()
{
	if (GET_PLAYER->Get_TileIdx() == m_iTileIdx && m_iTileIdx != 0)
	{
		if (m_iIsClosed == 0)
		{
			Interact_Stair();
			return OBJ_NEXTSCENE;
		}
		else
		{
			if (m_bIsPlayerOnTile == false )
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"sfx_error.wav", SOUND_EFFECT, 0.8f);
				m_bIsPlayerOnTile = true;
			}
		}
	}
	else
	{
		m_bIsPlayerOnTile = false;
	}





	__super::Update_Rect();
	//m_iIsClosed = 1;
    return OBJ_NOEVENT;
}

void CStair::Late_Update()
{
	
	//if (static_cast<CPlayer*>(GET_PLAYER)->Get_HeadTileIdx() == m_iTileIdx)
	//{
	//	{
	//		if (m_bIsPlayerOnTile == false)
	//		{
	//			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	//			CSoundMgr::Get_Instance()->PlaySound(L"sfx_error.wav", SOUND_EFFECT, 0.8f);
	//			m_bIsPlayerOnTile = true;
	//		}
	//	}
	//}
	//else
	//{
	//	m_bIsPlayerOnTile = false;
	//}
}

void CStair::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
    //Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	BitBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		TILECX,
		TILECY,
		hMemDC,
		52 * m_iIsClosed + 2,
		2,
		SRCCOPY);
}

void CStair::Release()
{
}

void CStair::Interact_Stair()
{
	CSceneMgr::Get_Instance()->Set_Scene(m_iNextScene);
}
