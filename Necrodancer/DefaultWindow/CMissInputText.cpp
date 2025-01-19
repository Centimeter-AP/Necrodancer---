#include "pch.h"
#include "CMissInputText.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CSoundMgr.h"

void CMissInputText::Initialize()
{
    m_tInfo.fX = (float)WINCX * 0.5f;
    m_tInfo.fY = (float)WINCY - 171.f;
    m_tInfo.fCX = 36.f;
    m_tInfo.fCY = 13.f;

    m_pImgKey = L"InputMiss";
    m_fSpeed = 1.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Text/TEMP_missed.bmp", L"InputMiss");
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT2);
	CSoundMgr::Get_Instance()->PlaySound(L"sfx_missedbeat.ogg", SOUND_EFFECT2, 0.9f);
    m_eRender = RENDER_LETTERBOX;
}

int CMissInputText::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
    --m_iMovingOffsetY;
	if (m_iMovingOffsetY <= -30)
	{
		m_bDead = true;
	}   

	__super::Update_Rect();
    return OBJ_NOEVENT;
}

void CMissInputText::Late_Update()
{
}

void CMissInputText::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

    int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    GdiTransparentBlt(hDC,
        m_tRect.left,
        m_tRect.top + m_iMovingOffsetY,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hMemDC,
        0,
        0,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        RGB(255, 0, 255));
}

void CMissInputText::Release()
{
}
