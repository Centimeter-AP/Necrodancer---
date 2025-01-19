#include "pch.h"
#include "CGoldenKey.h"
#include "CTileMgr.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CSceneMgr.h"

void CGoldenKey::Initialize()
{
    m_tInfo.fCX = TILECX;
    m_tInfo.fCY = TILECY;
    m_pImgKey = L"goldenkey";
    m_eRender = RENDER_GAMEOBJECT;
    m_iTileIdx = 365;
    //365
	m_fSpeed = 2.f;
    m_bOnMap = true;
    m_tInfo.fX = (*CTileMgr::Get_Instance()->Get_TileVec())[m_iTileIdx]->Get_Info().fX;
    m_tInfo.fY = (*CTileMgr::Get_Instance()->Get_TileVec())[m_iTileIdx]->Get_Info().fY;

    CTileMgr::Get_Instance()->Set_TileObject(m_iTileIdx, TOBJ_ITEM, this);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Item/golden_key.bmp", L"goldenkey");
}

int CGoldenKey::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
    if (m_bOnMap)
    {
        Find_Player_OnSameTile();

        //m_eRender = RENDER_MAPITEM;
        m_iFrameTicker += (int)m_fSpeed;

        switch (m_iFrameTicker)
        {
        case 20:
        case 40:
        case 60:
        case 80:
            m_iAnimationOffsetY += (int)m_fSpeed;
            break;
        case 0:
        case 100:
            m_fSpeed *= -1.f;
            break;
        default:
            break;
        }
    }
    else
    {
        m_eRender = RENDER_UI;

    }
    __super::Update_Rect();
    return 0;
}

void CGoldenKey::Late_Update()
{

}

void CGoldenKey::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

    int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    if (m_bOnMap)
    {
        //if (m_bIsPlayerOnTile == false)
        GdiTransparentBlt(hDC,			// 복사 받을 DC
            m_tRect.left + iScrollX,	// 복사 받을 위치 좌표 X, Y	
            m_tRect.top - 24 + iScrollY + m_iAnimationOffsetY,
            (int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
            (int)m_tInfo.fCY,
            hMemDC,						// 복사할 이미지 DC	
            0,							// 비트맵 출력 시작 좌표(Left, top)
            0,
            (int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
            (int)m_tInfo.fCY,
            RGB(255, 0, 255));		// 제거할 색상
    }
    else
    {
        if (CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_LOBBY)
        {
            GdiTransparentBlt(hDC,			// 복사 받을 DC
                220,	// 복사 받을 위치 좌표 X, Y	
                100,
                (int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
                (int)m_tInfo.fCY,
                hMemDC,						// 복사할 이미지 DC	
                0,							// 비트맵 출력 시작 좌표(Left, top)
                0,
                (int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
                (int)m_tInfo.fCY,
                RGB(255, 0, 255));		// 제거할 색상
            return;
        }
        GdiTransparentBlt(hDC,			// 복사 받을 DC
            220,	// 복사 받을 위치 좌표 X, Y	
            100,
            (int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
            (int)m_tInfo.fCY,
            hMemDC,						// 복사할 이미지 DC	
            0,							// 비트맵 출력 시작 좌표(Left, top)
            0,
            (int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
            (int)m_tInfo.fCY,
            RGB(255, 0, 255));		// 제거할 색상
    }
}

void CGoldenKey::Release()
{
}
