#include "pch.h"
#include "CMonsterHP.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"

void CMonsterHP::Initialize()
{
    m_tInfo.fCX = 24.f;
    m_tInfo.fCY = 22.f;
    m_pImgKey = L"MonsterHeart";
    m_iHP = m_pTarget->Get_HP();
    m_iMaxHP = m_pTarget->Get_MaxHP();
    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 1;
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/UI/MonsterHeart.bmp", L"MonsterHeart");
    m_eRender = RENDER_OBJUI;
}

int CMonsterHP::Update()
{
    m_tInfo.fX = m_pTarget->Get_Info().fX;
    m_tInfo.fY = m_pTarget->Get_Info().fY - 48.f;
    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CMonsterHP::Late_Update()
{
    m_iHP = m_pTarget->Get_HP();
}

void CMonsterHP::Render(HDC hDC)
{
    int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

    switch (m_iMaxHP)
    {
    case 1:
    {
        GdiTransparentBlt(hDC,							//个烹
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
        break;
    case 2:
    {
        GdiTransparentBlt(hDC,							//个烹
            m_tRect.left + iScrollX - (int)m_tInfo.fCX / 2,
            m_tRect.top + iScrollY,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            hMemDC,
            (int)m_tInfo.fCX * m_tFrame.iFrameStart,
            0,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            RGB(255, 0, 255));
        if (m_iHP == 1)
        {
            GdiTransparentBlt(hDC,							//个烹
                m_tRect.left + iScrollX + (int)m_tInfo.fCX / 2,
                m_tRect.top + iScrollY,
                (int)m_tInfo.fCX,
                (int)m_tInfo.fCY,
                hMemDC,
                (int)m_tInfo.fCX *1,
                0,
                (int)m_tInfo.fCX,
                (int)m_tInfo.fCY,
                RGB(255, 0, 255));
        }
        else
        {
            GdiTransparentBlt(hDC,							//个烹
                m_tRect.left + iScrollX + (int)m_tInfo.fCX / 2,
                m_tRect.top + iScrollY,
                (int)m_tInfo.fCX,
                (int)m_tInfo.fCY,
                hMemDC,
                (int)m_tInfo.fCX*0,
                0,
                (int)m_tInfo.fCX,
                (int)m_tInfo.fCY,
                RGB(255, 0, 255));
        }
    }
        break;
    case 3:
    {
        GdiTransparentBlt(hDC,							
            m_tRect.left + iScrollX - (int)m_tInfo.fCX,
            m_tRect.top + iScrollY,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            hMemDC,
            (int)m_tInfo.fCX * m_tFrame.iFrameStart,
            0,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            RGB(255, 0, 255));
        if (m_iMaxHP - m_iHP <= 1)
        {
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
        if (m_iMaxHP == m_iHP)
        {
            GdiTransparentBlt(hDC,							
                m_tRect.left + iScrollX + (int)m_tInfo.fCX,
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
        else if (m_iMaxHP - m_iHP == 2)
        {
            GdiTransparentBlt(hDC,							
                m_tRect.left + iScrollX,
                m_tRect.top + iScrollY,
                (int)m_tInfo.fCX,
                (int)m_tInfo.fCY,
                hMemDC,
                (int)m_tInfo.fCX * 1,
                0,
                (int)m_tInfo.fCX,
                (int)m_tInfo.fCY,
                RGB(255, 0, 255));
            GdiTransparentBlt(hDC,							
                m_tRect.left + iScrollX + (int)m_tInfo.fCX,
                m_tRect.top + iScrollY,
                (int)m_tInfo.fCX,
                (int)m_tInfo.fCY,
                hMemDC,
                (int)m_tInfo.fCX* 1,
                0,
                (int)m_tInfo.fCX,
                (int)m_tInfo.fCY,
                RGB(255, 0, 255));
        }
        else if (m_iMaxHP - m_iHP == 1)
        {
            GdiTransparentBlt(hDC,
                m_tRect.left + iScrollX + (int)m_tInfo.fCX,
                m_tRect.top + iScrollY,
                (int)m_tInfo.fCX,
                (int)m_tInfo.fCY,
                hMemDC,
                (int)m_tInfo.fCX * 1,
                0,
                (int)m_tInfo.fCX,
                (int)m_tInfo.fCY,
                RGB(255, 0, 255));
        }
    }
        break;
    case 4:
    {

    }
        break;
    case 5:
    {
        int emptyheart = m_iMaxHP - m_iHP;
        m_tRect.left -= (int)m_tInfo.fCX * 2;
        if (emptyheart == 0)
        {
            for (int i = 0; i < m_iMaxHP - emptyheart; ++i)
            {
                GdiTransparentBlt(hDC,
                    m_tRect.left + iScrollX + (int)m_tInfo.fCX * i,
                    m_tRect.top + iScrollY,
                    (int)m_tInfo.fCX,
                    (int)m_tInfo.fCY,
                    hMemDC,
                    (int)m_tInfo.fCX * 0,
                    0,
                    (int)m_tInfo.fCX,
                    (int)m_tInfo.fCY,
                    RGB(255, 0, 255));
            }
        }
        else if (emptyheart != 0)
        {
            for (int i = 0; i < m_iMaxHP - emptyheart; ++i)
            {
                GdiTransparentBlt(hDC,
                    m_tRect.left + iScrollX + (int)m_tInfo.fCX * i,
                    m_tRect.top + iScrollY,
                    (int)m_tInfo.fCX,
                    (int)m_tInfo.fCY,
                    hMemDC,
                    (int)m_tInfo.fCX * 0,
                    0,
                    (int)m_tInfo.fCX,
                    (int)m_tInfo.fCY,
                    RGB(255, 0, 255));
                if (i + 1 == m_iMaxHP - emptyheart)
                    m_tRect.left += (int)m_tInfo.fCX * (i + 1);
            }
            for (int i = 0; i < emptyheart; ++i)
            {
                GdiTransparentBlt(hDC,
                    m_tRect.left + iScrollX + (int)m_tInfo.fCX * i,
                    m_tRect.top + iScrollY,
                    (int)m_tInfo.fCX,
                    (int)m_tInfo.fCY,
                    hMemDC,
                    (int)m_tInfo.fCX * 1,
                    0,
                    (int)m_tInfo.fCX,
                    (int)m_tInfo.fCY,
                    RGB(255, 0, 255));
            }
        }
    }
        break;
    default:
        break;
    }



    //if (m_iMaxHP ==)
    //{
    //    for (int i = 0; i < m_iMaxHP; ++i)
    //    {
    //        GdiTransparentBlt(hDC,							//个烹
    //            m_tRect.left + iScrollX - i * (int)m_tInfo.fCX,
    //            m_tRect.top + iScrollY,
    //            (int)m_tInfo.fCX,
    //            (int)m_tInfo.fCY,
    //            hMemDC,
    //            (int)m_tInfo.fCX * m_tFrame.iFrameStart,
    //            0,
    //            (int)m_tInfo.fCX,
    //            (int)m_tInfo.fCY,
    //            RGB(255, 0, 255));
    //    }
    //}

    //GdiTransparentBlt(hDC,							//个烹
    //    m_tRect.left + iScrollX,
    //    m_tRect.top + iScrollY,
    //    (int)m_tInfo.fCX,
    //    (int)m_tInfo.fCY,
    //    hMemDC,
    //    (int)m_tInfo.fCX * m_tFrame.iFrameStart,
    //    0,
    //    (int)m_tInfo.fCX,
    //    (int)m_tInfo.fCY,
    //    RGB(255, 0, 255));
}

void CMonsterHP::Release()
{
}

void CMonsterHP::Set_Target(CObj* _rhs)
{
    m_pTarget = _rhs;
}
