#include "pch.h"
#include "CCoralDrum.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "CObjMgr.h"
#include "CBeatMgr.h"
#include "CSoundMgr.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CWaterTile.h"


void CCoralDrum::Initialize()
{
    //드럼 82 110
//본체 86 120
//호른 72 116
//키보드 52 110 
    m_iImgCX = 82;
    m_iImgCY = 110;
    m_tInfo.fCX = 82.f;
    m_tInfo.fCY = 48.f;
    m_fSpeed = 6.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Monster/Boss/coralriff_drums.bmp", L"Drum");
    m_pvecTile = CTileMgr::Get_Instance()->Get_TileVec();
    m_iHeadTileIdx = m_iTileIdx = Find_MyTileIdx();
    CTileMgr::Get_Instance()->Set_TileObject(m_iHeadTileIdx, TOBJ_ENTITY, this);

    m_tInfo.fX = (*m_pvecTile)[m_iTileIdx]->Get_Info().fX;
    m_tInfo.fY = (*m_pvecTile)[m_iTileIdx]->Get_Info().fY;
    m_pTarget = GET_PLAYER;
    m_eDir = DIR_UP;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 100;
    m_tFrame.dwTime = GetTickCount64();

    m_pImgKey = L"Drum";
    m_fJumpPower = 9.5f;
    Get_TileX();
    Get_TileY();
    m_eRender = RENDER_GAMEOBJECT;
    m_iMaxHP = 1;
    m_iHP = 1;
    m_iDamage = 3;
    m_iOrigTileIdx = m_iTileIdx;

    m_HP_UI.Set_Target(this);
    m_HP_UI.Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_UI, &m_HP_UI);
}

int CCoralDrum::Update()
{
    if (m_bDead || m_iHP == 0)
    {
        CBeatMgr::Get_Instance()->Plus_BeatCombo();
        CSoundMgr::Get_Instance()->ChangeChannelVolume(SOUND_BOSS1, -0.1f);

        return OBJ_DEAD;
    }
    if (BEATMGR->Get_ObjectAbleToMove() == true)
    {
        if (m_bMoveStart == true)
        {
            if (m_eCurState == SHAKE_ACT && m_iBeatPassed == 1)
            {
                m_eCurState = DIVEDOWN_ACT; m_iBeatPassed = 0;
            }
            else if (m_eCurState == DIVEDOWN_ACT && m_iBeatPassed == 2)
            {
                m_eCurState = DIVEUP_ACT; m_iBeatPassed = 0;
            }
            else if (m_eCurState == DIVEUP_ACT && m_iBeatPassed == 1)
            {
                m_eCurState = ATTACKREADY_ACT; m_iBeatPassed = 0;
            }
            else if (m_eCurState == ATTACKREADY_ACT && m_iBeatPassed == 3)
            {
                m_eCurState = IDLE_ACT; m_iBeatPassed = 0; m_bMoveStart = false;
            }

            switch (m_eCurState)
            {
            case CCoralInst::SHAKE_ACT:
                //쉐낏하기 애니메이션
                
                break;
            case CCoralInst::DIVEDOWN_ACT:
                // 사운드, 이펙트 
                if (m_bWaterIn == false)
                {
                    CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
                    CSoundMgr::Get_Instance()->PlaySound(L"mov_water_in.ogg", SOUND_EFFECT, g_fVolume);
                    m_bWaterIn = true;
                }
                break;
            case CCoralInst::DIVEUP_ACT:
                // 사운드, 이펙트...
                m_bWaterIn = false;
                CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
                CSoundMgr::Get_Instance()->PlaySound(L"mov_water_out.ogg", SOUND_EFFECT, g_fVolume);
                Set_HeadPositionIdx();
                CTileMgr::Get_Instance()->Remove_TileObject(m_iTileIdx, TOBJ_ENTITY);
                CTileMgr::Get_Instance()->Set_TileObject(m_iHeadTileIdx, TOBJ_ENTITY, this);
                m_iTileIdx = m_iHeadTileIdx;
                m_tInfo.fX = (*m_pvecTile)[m_iTileIdx]->Get_Info().fX;
                m_tInfo.fY = (*m_pvecTile)[m_iTileIdx]->Get_Info().fY;
                CObjMgr::Get_Instance()->Add_Object(OBJ_STAIR, CAbstractFactory<CWaterTile>::Create(m_iTileIdx));

                break;
            case CCoralInst::ATTACKREADY_ACT:
                if (m_iBeatPassed > 0)
                {
                    int iPHTileIdx = static_cast<CPlayer*>(m_pTarget)->Get_HeadTileIdx();
                    if (m_iTileIdx + 1 == iPHTileIdx || m_iTileIdx + TILEX == iPHTileIdx
                        || m_iTileIdx - 1 == iPHTileIdx || m_iTileIdx - TILEX == iPHTileIdx)
                    {
                        GET_PLAYER->Set_HP(m_iDamage);
                        if (static_cast<CPlayer*>(GET_PLAYER)->Get_ItemSlot(ITEM_ARMOR).empty() == false)
                        {
                            GET_PLAYER->Set_HP(m_iDamage);
                        }
                        CSoundMgr::Get_Instance()->StopSound(SOUND_VOCAL);
                        CSoundMgr::Get_Instance()->PlaySound(L"vo_cad_hurt_01.wav", SOUND_VOCAL, g_fVolume);
                    }
                }
                break;
            case CCoralInst::IDLE_ACT:
                CTileMgr::Get_Instance()->Remove_TileObject(m_iTileIdx, TOBJ_ENTITY);
                CTileMgr::Get_Instance()->Set_TileObject(m_iOrigTileIdx, TOBJ_ENTITY, this);
                m_iTileIdx = m_iOrigTileIdx;
                m_tInfo.fX = (*m_pvecTile)[m_iTileIdx]->Get_Info().fX;
                m_tInfo.fY = (*m_pvecTile)[m_iTileIdx]->Get_Info().fY;
                m_iBeatPassed = 0; m_bMoveStart = false;
                break;
            default:
                break;
            }
            ++m_iBeatPassed;

        }
    }
    m_iTileIdx = Find_MyTileIdx();
    m_iShakeAnimation *= -1;
    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CCoralDrum::Late_Update()
{
    __super::Move_Frame();
}

void CCoralDrum::Render(HDC hDC)
{
    if (m_eCurState != DIVEDOWN_ACT)
    {
        HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

        int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
        int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

        //Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
        if (m_eCurState == SHAKE_ACT || m_eCurState == ATTACKREADY_ACT)
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
}

void CCoralDrum::Release()
{
    CObjMgr::Get_Instance()->Delete_Object(OBJ_UI, &m_HP_UI);
}
