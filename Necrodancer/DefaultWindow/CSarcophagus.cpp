#include "pch.h"
#include "CSarcophagus.h"
#include "CBmpMgr.h"
#include "CTileMgr.h"
#include "CScrollMgr.h"

void CSarcophagus::Initialize()
{
    m_tInfo.fCX = TILECX;
    m_tInfo.fCY = TILECY;
    m_pImgKey = L"sarcophagus";
    m_eRender = RENDER_GAMEOBJECT;
    m_iTileIdx = 833;


    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 100;
    m_tFrame.dwTime = GetTickCount64();

    m_tInfo.fX = (*CTileMgr::Get_Instance()->Get_TileVec())[833]->Get_Info().fX;
    m_tInfo.fY = (*CTileMgr::Get_Instance()->Get_TileVec())[833]->Get_Info().fY;

    CTileMgr::Get_Instance()->Set_TileObject(833, TOBJ_ENTITY, this);
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/sarcophagus.bmp", L"sarcophagus");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/mom.bmp", L"mom");
}

int CSarcophagus::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}   
    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CSarcophagus::Late_Update()
{
	__super::Move_Frame();
}

void CSarcophagus::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

    int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    if (m_bIsOpen == false)
    {
        GdiTransparentBlt(hDC,			// 복사 받을 DC
            m_tRect.left + iScrollX,	// 복사 받을 위치 좌표 X, Y	
            m_tRect.top + iScrollY,
            (int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
            (int)m_tInfo.fCY,
            hMemDC,						// 복사할 이미지 DC	
            0,					// 비트맵 출력 시작 좌표(Left, top)
            0,
            (int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
            (int)m_tInfo.fCY,
            RGB(255, 0, 255));		// 제거할 색상
    }
    else
    {
        HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"mom");

        GdiTransparentBlt(hDC,
            m_tRect.left + iScrollX,
            m_tRect.top - 24 + iScrollY,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            hMemDC,
            (int)m_tInfo.fCX * m_tFrame.iFrameStart,
            0,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            RGB(255, 0, 255));
    }
}

void CSarcophagus::Release()
{
}
