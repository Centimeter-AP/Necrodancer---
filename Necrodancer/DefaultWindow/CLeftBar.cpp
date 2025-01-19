#include "pch.h"
#include "CLeftBar.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CBeatMgr.h"
#include "CSceneMgr.h"

void CLeftBar::Initialize()
{
    m_tInfo = { 0.f , (float)WINCY - 145.f, 12.f, 60.f };
    m_pImgKey = L"Beatbar";
    m_fSpeed = 1.f;

    m_eRender = RENDER_BEAT;
}

int CLeftBar::Update()
{
    if (m_bDead)
        return OBJ_DEAD;
    if (CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_BOSS)
        m_tInfo.fX += m_fSpeed * 4.f * (126.f / 115.f);
    else if (CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_STAGEONE)
        m_tInfo.fX += m_fSpeed * 4.f;

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CLeftBar::Late_Update()
{
    if (m_fSpeed < 0)
    {
        if (m_tInfo.fX < (float)WINCX * 0.5f - CBeatMgr::Get_Instance()->Get_BeatJudgementPx())
        {
            m_bDead = true;
            if (CBeatMgr::Get_Instance()->Get_BeatMissed() == false)
            {
                CBeatMgr::Get_Instance()->Lose_BeatCombo();
                CBeatMgr::Get_Instance()->Set_BeatMissed(true);
            }
            else        // 박자 놓친 상태일 때
            {           // 오브젝트 행동 가능 부여
                CBeatMgr::Get_Instance()->Set_ObjectAbleToMove(true);
            }
        }
    }
    else
    {
        if (m_tInfo.fX > (float)WINCX * 0.5f + CBeatMgr::Get_Instance()->Get_BeatJudgementPx())
        {
            m_bDead = true;
        //    if (CBeatMgr::Get_Instance()->Get_BeatMissed() == false)
        //    {
        //        CBeatMgr::Get_Instance()->Set_BeatMissed(true);
        //    }
        }
        //else        // 박자 놓친 상태일 때
        //{           // 오브젝트 행동 가능 부여
        //    CBeatMgr::Get_Instance()->Set_ObjectAbleToMove(true);
        //}
    }
}

void CLeftBar::Render(HDC hDC)
{
    Graphics graphics(hDC);

    Image image(L"../content/texture/UI/BeatBar.png");

    if (m_fSpeed < 0)
    {
        if (m_tInfo.fX > (float)WINCX * 0.5f)
        {
            graphics.DrawImage(&image, (int)m_tRect.left, (int)m_tRect.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY);
        }
    }
    else
    {
        if (m_tInfo.fX < (float)WINCX * 0.5f)
        {
            graphics.DrawImage(&image, (int)m_tRect.left, (int)m_tRect.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY);
        }
    }



    //graphics.DrawImage(&image, (int)m_tRect.left, (int)m_tRect.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY);

    //Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CLeftBar::Release()
{
}
