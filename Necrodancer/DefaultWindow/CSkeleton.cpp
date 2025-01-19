#include "pch.h"
#include "CSkeleton.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "CObjMgr.h"
#include "CBeatMgr.h"
#include "CSoundMgr.h"

void CSkeleton::Initialize()
{
    m_tInfo.fCX = 48.f;
    m_tInfo.fCY = 50.f;
    m_fSpeed = 6.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Monster/Skeletons.bmp", L"Skeleton");
    m_pvecTile = CTileMgr::Get_Instance()->Get_TileVec();
    m_iHeadTileIdx = m_iTileIdx = Find_MyTileIdx();

    m_tInfo.fX = (*m_pvecTile)[m_iTileIdx]->Get_Info().fX;
    m_tInfo.fY = (*m_pvecTile)[m_iTileIdx]->Get_Info().fY - 24.f;
    m_pTarget = GET_PLAYER;
    m_eDir = DIR_UP;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 100;
    m_tFrame.dwTime = GetTickCount64();

    m_iMoney = 50;
    m_pImgKey = L"Skeleton";
    m_fJumpPower = 9.5f;
    Get_TileX();
    Get_TileY();
    m_eRender = RENDER_GAMEOBJECT;
    m_iMaxHP = 1;
    m_iHP = 1;
    m_iDamage = 1;

    m_HP_UI.Set_Target(this);
    m_HP_UI.Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_UI, &m_HP_UI);
}

int CSkeleton::Update()
{
    if (m_bDead || m_iHP == 0)
    {
        CBeatMgr::Get_Instance()->Plus_BeatCombo();
        CSoundMgr::Get_Instance()->StopSound(SOUND_MONDEATH2);
        CSoundMgr::Get_Instance()->PlaySound(L"en_skel_death.ogg", SOUND_MONDEATH2, 0.2f);
        return OBJ_DEAD;
    }

    if (m_bPlayerFound)
    {
        if (BEATMGR->Get_ObjectAbleToMove() == true)
        {
            if (m_eCurState == AFTER_ACT)
            {
                //BEATMGR->Set_ObjectAbleToMove(false);
                m_eCurState = BEFORE_ACT;
                m_iHeadTileIdx = m_iTileIdx;
                m_iTileIdx = Find_MyTileIdx();
                m_iBeforeAct = 1;
                return OBJ_NOEVENT;
            }
            else
            {
                m_iBeforeAct = 0;
                m_eCurState = AFTER_ACT;
            }

            m_iTileIdx = Find_MyTileIdx();
            if (m_pTarget != nullptr)
            {
                Find_Player();
            }
            if (Can_Move())
            {
                m_bMove = true;
            }
            else
            {
                m_iHeadTileIdx = m_iTileIdx;
            }
            //BEATMGR->Set_ObjectAbleToMove(false);
        }
    }

    Jumping();

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CSkeleton::Late_Update()
{
    int iDistance = abs(m_pTarget->Get_TileX() - Get_TileX()) + abs(m_pTarget->Get_TileY() - Get_TileY());
    if (m_bPlayerFound == false)
    {
        if (iDistance <= 10)
        {
            m_bPlayerFound = true;
        }
    }
    __super::Move_Frame();

}

void CSkeleton::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Skeleton");

    int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    //Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

    GdiTransparentBlt(hDC,							
        m_tRect.left + iScrollX,
        m_tRect.top + iScrollY,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hMemDC,
        (int)m_tInfo.fCX * m_tFrame.iFrameStart + m_iActMotionOffset * m_iBeforeAct,
        (int)m_tInfo.fCY * m_tFrame.iMotion,
        PLAYERCX,
        PLAYERCY,
        RGB(255, 0, 255));

    m_HP_UI.Render(hDC);
}

void CSkeleton::Release()
{
    CObjMgr::Get_Instance()->Delete_Object(OBJ_UI, &m_HP_UI);
}

void CSkeleton::Play_HitSound()
{
    CSoundMgr::Get_Instance()->StopSound(SOUND_MONHIT2);
    CSoundMgr::Get_Instance()->PlaySound(L"en_skel_hit_01.wav", SOUND_MONHIT2, 0.2f);
}

