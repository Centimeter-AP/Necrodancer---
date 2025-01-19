#include "pch.h"
#include "CBlueSlime.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "CObjMgr.h"
#include "CBeatMgr.h"
#include "CSoundMgr.h"
#include "CMonsterHP.h"
#include "CGold.h"
#include "CAbstractFactory.h"

void CBlueSlime::Initialize()
{
    m_tInfo.fCX = 52.f;
    m_tInfo.fCY = 50.f;
    m_fSpeed = 6.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Monster/Blueslime_L.bmp", L"Blueslime_L");
    m_pvecTile = CTileMgr::Get_Instance()->Get_TileVec();
    m_iHeadTileIdx = m_iTileIdx = Find_MyTileIdx();
    m_iSelectedIndex[0] = m_iTileIdx;
    if (rand() % 2)
    {
        m_iSelectedIndex[1] = m_iTileIdx - TILEX;
    }
    else
    {
        m_iSelectedIndex[1] = m_iTileIdx + TILEX;
    }
    m_tInfo.fX = (*m_pvecTile)[m_iTileIdx]->Get_Info().fX;
    m_tInfo.fY = (*m_pvecTile)[m_iTileIdx]->Get_Info().fY - 24.f;
    m_pTarget = GET_PLAYER;
    m_eDir = DIR_UP;

    m_iMoney = 20;
    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 100;
    m_tFrame.dwTime = GetTickCount64();

    m_pImgKey = L"Blueslime_L";
    m_fJumpPower = 9.5f;
    Get_TileX();
    Get_TileY();
    m_eRender = RENDER_GAMEOBJECT;
    m_iMaxHP = 2;
    m_iHP = 2;
    m_iDamage = 2;

    m_HP_UI.Set_Target(this);
    m_HP_UI.Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_UI, &m_HP_UI);
}

int CBlueSlime::Update()
{
    if (m_bDead || m_iHP == 0)
    {
        //CObjMgr::Get_Instance()->Add_Object(OBJ_GOLD, CAbstractFactory<CGold>::Create(m_iTileIdx));
        //static_cast<CItem*>(CObjMgr::Get_Instance()->Get_LastGold())->Set_Price(m_iMoney);
        CBeatMgr::Get_Instance()->Plus_BeatCombo();
        CSoundMgr::Get_Instance()->StopSound(SOUND_MONDEATH1);
        CSoundMgr::Get_Instance()->PlaySound(L"en_slime_death_01.wav", SOUND_MONDEATH1, 0.2f);
        return OBJ_DEAD;

    }

    if (BEATMGR->Get_ObjectAbleToMove() == true)
    {
        if (m_eCurState == AFTER_ACT)
        {
            m_eCurState = BEFORE_ACT;
            m_iHeadTileIdx = m_iTileIdx;
            m_iTileIdx = Find_MyTileIdx();
            m_tFrame.iMotion = 0;

            return OBJ_NOEVENT;
        }
        else
        {
            m_tFrame.iMotion = 1;
            if (m_eDir == DIR_UP)
                m_eDir = DIR_DOWN;
            else
                m_eDir = DIR_UP;

            m_eCurState = AFTER_ACT;
        }

        m_iTileIdx = Find_MyTileIdx();

        if (Can_Move())
        {
            m_bMove = true;
            if (m_iHeadTileIdx != m_iTileIdx && m_iHeadTileIdx != m_iSelectedIndex[0] && m_iHeadTileIdx != m_iSelectedIndex[1])
                m_bMove = false;
        }
        else
        {
            m_iHeadTileIdx = m_iTileIdx;
        }
        //BEATMGR->Set_ObjectAbleToMove(false);
    }

    //if (m_iTileIdx == m_iSelectedIndex[0])
    //{
    //    m_iHeadTileIdx = m_iSelectedIndex[1];
    //}
    //else
    //    m_iHeadTileIdx = m_iSelectedIndex[0];


    Jumping();

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CBlueSlime::Late_Update()
{
    __super::Move_Frame();
}

void CBlueSlime::Render(HDC hDC)
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

    //m_HP_UI.Render(hDC);
}

void CBlueSlime::Release()
{
    CObjMgr::Get_Instance()->Delete_Object(OBJ_UI, &m_HP_UI);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_GOLD, CAbstractFactory<CGold>::Create(m_iTileIdx));
 //   static_cast<CItem*>(CObjMgr::Get_Instance()->Get_LastGold())->Set_Price(m_iMoney);

}

void CBlueSlime::Play_HitSound()
{
    CSoundMgr::Get_Instance()->StopSound(SOUND_MONHIT1);
    CSoundMgr::Get_Instance()->PlaySound(L"en_slime_hit_01.wav", SOUND_MONHIT1, 0.2f);
}
