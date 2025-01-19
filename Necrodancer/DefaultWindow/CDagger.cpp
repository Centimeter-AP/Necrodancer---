#include "pch.h"
#include "CDagger.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "CObjMgr.h"

//26
void CDagger::Initialize()
{
    m_tInfo.fCX = 26.f;
    m_tInfo.fCY = 26.f;
    m_pImgKey = L"Dagger";
    m_fSpeed = 2.f;

    m_iDamage = 1;

    //m_iTileIdx = ((int)m_tInfo.fY / TILECY) * TILEX + ((int)m_tInfo.fX / TILECX);
    m_tInfo.fX = (*CTileMgr::Get_Instance()->Get_TileVec())[m_iTileIdx]->Get_Info().fX;
    m_tInfo.fY = (*CTileMgr::Get_Instance()->Get_TileVec())[m_iTileIdx]->Get_Info().fY - 24.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Item/Dagger.bmp", L"Dagger");
    m_eRender = RENDER_GAMEOBJECT;
    m_eItemType = ITEM_WEAPON;
    m_eWeaponType = DAGGER_TYPE;
    //m_pTarget = GET_PLAYER;
}

int CDagger::Update()
{
    if (m_bUsing)
    {
        m_tInfo.fX = m_tInfo.fY = 0.f;
        m_eRender = RENDER_EFFECT;
    }
    else if (m_bOnMap)
    {
        Find_Player_OnSameTile();
        m_eRender = RENDER_MAPITEM;
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

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CDagger::Late_Update()
{
    if (m_bOnMap)
    {
        Find_TileIdx_OnMap();
    }
}

void CDagger::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

    int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    if (m_bOnMap)
    {
        if (m_bIsPlayerOnTile == false)
        {
            //Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
            GdiTransparentBlt(hDC,			// 복사 받을 DC
                m_tRect.left + iScrollX,	// 복사 받을 위치 좌표 X, Y	
                m_tRect.top + iScrollY + m_iAnimationOffsetY,
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
    else
        return;
}

void CDagger::Release()
{
}
