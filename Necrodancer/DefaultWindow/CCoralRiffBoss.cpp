#include "pch.h"
#include "CCoralRiffBoss.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "CObjMgr.h"
#include "CBeatMgr.h"
#include "CSoundMgr.h"
#include "CCoralInst.h"
#include "CKeyMgr.h"
#include "CAbstractFactory.h"
#include "CSplash.h"
#include "CWaterTile.h"
#include "CPlayer.h"


void CCoralRiffBoss::Initialize()
{
    //드럼 82 110
//본체 86 120
//호른 72 116
//키보드 52 110 
    m_iImgCX = 86;
    m_iImgCY = 120;
    m_tInfo.fCX = 86.f;
    m_tInfo.fCY = 48.f;
    m_fSpeed = 6.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Monster/Boss/coralriff_head.bmp", L"Boss");
    m_pvecTile = CTileMgr::Get_Instance()->Get_TileVec();
    m_iHeadTileIdx = m_iTileIdx = Find_MyTileIdx();
    CTileMgr::Get_Instance()->Set_TileObject(m_iHeadTileIdx, TOBJ_ENTITY, this);

    m_tInfo.fX = (*m_pvecTile)[m_iTileIdx]->Get_Info().fX;
    m_tInfo.fY = (*m_pvecTile)[m_iTileIdx]->Get_Info().fY;
    m_pTarget = GET_PLAYER;
    m_eDir = DIR_DOWN;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 100;
    m_tFrame.dwTime = GetTickCount64();

    m_pImgKey = L"Boss";
    m_fJumpPower = 9.5f;
    Get_TileX();
    Get_TileY();
    m_eRender = RENDER_GAMEOBJECT;
    m_iMaxHP = 5;
    m_iHP = 5;
    m_iDamage = 6;
    m_iBeatPassed = 0;

    m_HP_UI.Set_Target(this);
    m_HP_UI.Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_UI, &m_HP_UI);
}

int CCoralRiffBoss::Update()
{
    if (m_bDead || m_iHP == 0)
    {
        CBeatMgr::Get_Instance()->Plus_BeatCombo();
        CSoundMgr::Get_Instance()->PlaySound(L"en_coralriff_death.ogg", SOUND_EFFECT2, 0.2f);
        CSoundMgr::Get_Instance()->PlaySound(L"vo_cad_yeah_02.wav", SOUND_EFFECT3, 0.2f);
        for (auto& pInst : m_vecInstrument)
        {
            pInst->Set_Dead();
        }
        return OBJ_DEAD;
    }
    if (CKeyMgr::Get_Instance()->Key_Down('Z'))
    {
        m_iPhasePassed += 1;
        m_iBeatPassed = 0;
    }
    m_iShakeAnimation *= -1;

    if (m_iPhasePassed > 0)
    {
        if (BEATMGR->Get_ObjectAbleToMove() == true)
        {
            if (m_iPhasePassed < 8)
            {
                Inst_Phase();
            }
            else
            {
                Move_Phase();
            }
            ++m_iBeatPassed;
        }
        if (m_ibMovePhase == true)
        {
            BossMove();
            
        }
    }


    //m_iTileIdx = Find_MyTileIdx();

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CCoralRiffBoss::Late_Update()
{
    __super::Move_Frame();
}

void CCoralRiffBoss::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

    int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    //Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

    //GdiTransparentBlt(hDC,
    //    m_tRect.left + iScrollX,
    //    m_tRect.top + iScrollY,
    //    (int)m_tInfo.fCX,
    //    (int)m_tInfo.fCY,
    //    hMemDC,
    //    (int)m_tInfo.fCX * m_tFrame.iFrameStart,
    //    (int)m_tInfo.fCY * m_tFrame.iMotion,
    //    (int)m_tInfo.fCX,
    //    (int)m_tInfo.fCY,
    //    RGB(255, 0, 255));
    if (m_eCurState == BEFORE_ACT)
        m_tRect.left += m_iShakeAnimation;
    GdiTransparentBlt(hDC,
        m_tRect.left + iScrollX,
        m_tRect.bottom - m_iImgCY + iScrollY,
        m_iImgCX,
        m_iImgCY,
        hMemDC,
        m_iImgCX * m_tFrame.iFrameStart,
        m_iImgCY * m_tFrame.iMotion,
        m_iImgCX,
        m_iImgCY,
        RGB(255, 0, 255));

    //m_HP_UI.Render(hDC);
}

void CCoralRiffBoss::Release()
{
    CObjMgr::Get_Instance()->Delete_Object(OBJ_UI, &m_HP_UI);
}

void CCoralRiffBoss::Play_HitSound()
{
    CSoundMgr::Get_Instance()->StopSound(SOUND_MONHIT2);
    CSoundMgr::Get_Instance()->PlaySound(L"en_coralriff_hit_01.ogg", SOUND_MONHIT2, 0.2f);
}

void CCoralRiffBoss::Teleport_Hit()
{
    int i = rand() % 4;
    m_iTileIdx = m_iTeleportPos[i];
    m_tInfo.fX = (*m_pvecTile)[m_iTileIdx]->Get_Info().fX;
    m_tInfo.fY = (*m_pvecTile)[m_iTileIdx]->Get_Info().fY;
}



void CCoralRiffBoss::Inst_Phase()
{
    if (m_iPhasePassed == 1)
    {
        if (m_iBeatPassed == 3)
        {
            m_iPhasePassed = 2;
            m_iBeatPassed = 0;
        }
    }
    else if (m_iPhasePassed > 1 && m_iPhasePassed < 6)
    {
        if (m_iBeatPassed == 1)
        {
            //srand(time(NULL));
            int i = rand() % 4 + 1;
            static_cast<CCoralInst*>(m_vecInstrument[(m_iPhasePassed - 2) * 2])->Goto_Player(i);
            static_cast<CCoralInst*>(m_vecInstrument[(m_iPhasePassed - 2) * 2 + 1])->Goto_Player(10 - i);

        }
        else if (m_iBeatPassed == 7)
        {
            ++m_iPhasePassed;
            m_iBeatPassed = 0;
        }
    }
    else if (m_iPhasePassed == 6)
    {
        if (m_iBeatPassed == 1)
        {
            static_cast<CCoralInst*>(m_vecInstrument[0])->Goto_Player(2);
            static_cast<CCoralInst*>(m_vecInstrument[2])->Goto_Player(8);
            static_cast<CCoralInst*>(m_vecInstrument[4])->Goto_Player(4);
            static_cast<CCoralInst*>(m_vecInstrument[6])->Goto_Player(6);
        }
        else if (m_iBeatPassed == 7)
        {
            ++m_iPhasePassed;
            m_iBeatPassed = 0;
        }
    }
    else if (m_iPhasePassed == 7)
    {
        if (m_iBeatPassed == 1)
        {
            static_cast<CCoralInst*>(m_vecInstrument[1])->Goto_Player(1);
            static_cast<CCoralInst*>(m_vecInstrument[3])->Goto_Player(9);
            static_cast<CCoralInst*>(m_vecInstrument[5])->Goto_Player(3);
            static_cast<CCoralInst*>(m_vecInstrument[7])->Goto_Player(7);
        }
        else if (m_iBeatPassed == 6)
        {
            CSoundMgr::Get_Instance()->StopSound(SOUND_BOSSEFFECT1);
            CSoundMgr::Get_Instance()->PlaySound(L"en_coralriff_cry.ogg", SOUND_BOSSEFFECT1, 0.25f);
            CSoundMgr::Get_Instance()->ChangeChannelVolume(SOUND_BOSS1, 0.25f);
            CSoundMgr::Get_Instance()->ChangeChannelVolume(SOUND_BOSS2, 0.25f);
            CSoundMgr::Get_Instance()->ChangeChannelVolume(SOUND_BOSS3, 0.25f);
            CSoundMgr::Get_Instance()->ChangeChannelVolume(SOUND_BOSS4, 0.25f);

            ++m_iPhasePassed;
            m_iBeatPassed = 0;
        }
    }
    else if (m_iPhasePassed >= 8)
    {
        return; 
    }

}

void CCoralRiffBoss::Move_Phase()
{
    if (m_iPhasePassed >= 8)
    {
        if (m_ibMovePhase == false)
        {
            m_ibMovePhase = true;
        }
        if (m_eCurState == AFTER_ACT)
        {
            m_eCurState = BEFORE_ACT;
            m_iHeadTileIdx = m_iTileIdx;
            m_iTileIdx = Find_MyTileIdx();
            m_iBeforeAct = 1;
            return ;
        }
        else
        {
            m_iBeforeAct = 0;
            m_eCurState = AFTER_ACT;
            m_iTileIdx = Find_MyTileIdx();

        }

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
            CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CSplash>::Create(m_iHeadTileIdx));
            CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CSplash>::Create(m_iHeadTileIdx + 1));
            CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CSplash>::Create(m_iHeadTileIdx - 1));
            CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CSplash>::Create(m_iHeadTileIdx - TILEX + 1));
            CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CSplash>::Create(m_iHeadTileIdx - TILEX - 1));
            CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CSplash>::Create(m_iHeadTileIdx - TILEX * 2));
            CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CSplash>::Create(m_iHeadTileIdx - TILEX * 2 + 1));
            CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CSplash>::Create(m_iHeadTileIdx - TILEX * 2 - 1));
            int playerheadtile = static_cast<CPlayer*>(GET_PLAYER)->Get_HeadTileIdx();
            if (m_iHeadTileIdx == playerheadtile || m_iHeadTileIdx + 1 == playerheadtile
               || m_iHeadTileIdx - 1 == playerheadtile || m_iHeadTileIdx - TILEX + 1 == playerheadtile
               || m_iHeadTileIdx - TILEX - 1 == playerheadtile || m_iHeadTileIdx - TILEX * 2 == playerheadtile
               || m_iHeadTileIdx - TILEX * 2 + 1 == playerheadtile || m_iHeadTileIdx - TILEX * 2 - 1 == playerheadtile)
            {
                GET_PLAYER->Set_HP(m_iDamage);
                if (static_cast<CPlayer*>(GET_PLAYER)->Get_ItemSlot(ITEM_ARMOR).empty() == false)
                {
                    GET_PLAYER->Set_HP(m_iDamage);
                }
                CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
                CSoundMgr::Get_Instance()->PlaySound(L"vo_cad_hurt_01.wav", SOUND_EFFECT, g_fVolume);
            }
        }
    }
}

void CCoralRiffBoss::Set_InstTilePos()
{
    CTileMgr::Get_Instance()->Set_TileObject(m_iTileIdx, TOBJ_ENTITY, this);
    for (auto& pInst : m_vecInstrument)
    {
        static_cast<CCoralInst*>(pInst)->Set_TilePos();
    }

}
