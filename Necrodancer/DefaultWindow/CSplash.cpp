#include "pch.h"
#include "CSplash.h"
#include "Define.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"


void CSplash::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
	m_pImgKey = L"Splash";
	//m_iTileIdx = Find_MyTileIdx();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Effect/Splash_2.bmp", L"Splash");

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 4;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 80;
    m_tFrame.dwTime = GetTickCount64();

    m_eRender = RENDER_GAMEOBJECT;
}

int CSplash::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

#ifdef  _DEBUG

    cout << "¹° Å¸ÀÏ : " << m_iTileIdx << endl;

#endif //  _DEBUG


	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CSplash::Late_Update()
{
	__super::Move_Frame();
    if (m_tFrame.iFrameStart == 4)
    {
        m_bDead = true;
    }
}

void CSplash::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

    int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


    GdiTransparentBlt(hDC,
        m_tRect.left + iScrollX,
        m_tRect.top + iScrollY,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hMemDC,
        (int)m_tInfo.fCX * m_tFrame.iFrameStart,
        0,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        RGB(255, 0, 255));
}

void CSplash::Release()
{
}
