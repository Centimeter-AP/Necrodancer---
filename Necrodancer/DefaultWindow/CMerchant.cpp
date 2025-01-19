#include "pch.h"
#include "CMerchant.h"
#include "CSoundMgr.h"
#include "CBmpMgr.h"
#include "CTileMgr.h"
#include "CObjMgr.h"
#include "CScrollMgr.h"

void CMerchant::Initialize()
{
    m_tInfo.fCX = 94.f;
    m_tInfo.fCY = 76.f;
    m_fSpeed = 6.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Monster/shopkeeper.bmp", L"shopkeeper");
    m_iTileIdx = Find_MyTileIdx();

    m_tInfo.fX = (*(CTileMgr::Get_Instance()->Get_TileVec()))[m_iTileIdx]->Get_Info().fX;
    m_tInfo.fY = (*(CTileMgr::Get_Instance()->Get_TileVec()))[m_iTileIdx]->Get_Info().fY - 24.f;
    m_pTarget = GET_PLAYER;
    m_eDir = DIR_UP;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 150;
    m_tFrame.dwTime = GetTickCount64();

    m_pImgKey = L"shopkeeper";
    m_eRender = RENDER_GAMEOBJECT;

}

int CMerchant::Update()
{
	if (m_bDead)
		return OBJ_DEAD;	

	if (CSoundMgr::Get_Instance()->IsChannelPeakLevelAboveThreshold(SOUND_MERCHANT) == true)
	{
    	m_bIsSinging = true;
        m_tFrame.iMotion = 1;
	}
    else
    {
        m_bIsSinging = false;
		m_tFrame.iMotion = 0;   
    }
	__super::Update_Rect();
    return OBJ_NOEVENT;
}

void CMerchant::Late_Update()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
    {
        ++m_tFrame.iFrameStart;
        if (m_tFrame.iFrameStart % 2)
            m_tFrame.dwSpeed = 50;
        else
            m_tFrame.dwSpeed = 450;
        if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
            m_tFrame.iFrameStart = 0;

        m_tFrame.dwTime = GetTickCount64();
    }
    int iDistance = abs(m_pTarget->Get_TileX() - Get_TileX()) + abs(m_pTarget->Get_TileY() - Get_TileY());
    float iVolume = 0.6f - (float)iDistance / 15.f;
    if (iVolume < 0.f)
		iVolume = 0.f;
	CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_MERCHANT, iVolume);
}

void CMerchant::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

    int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    //Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

    GdiTransparentBlt(hDC,
        m_tRect.left + iScrollX,
        m_tRect.top + iScrollY,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hMemDC,
        (int)m_tInfo.fCX * m_tFrame.iFrameStart,
        (int)m_tInfo.fCY * m_tFrame.iMotion,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        RGB(255, 0, 255));

}

void CMerchant::Release()
{
}
