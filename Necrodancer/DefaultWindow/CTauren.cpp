#include "pch.h"
#include "CTauren.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "CObjMgr.h"
#include "CBeatMgr.h"
#include "CSoundMgr.h"
#include "CPlayer.h"
#include "CStair.h"

void CTauren::Initialize()
{
    m_tInfo.fCX = 100.f;
    m_tInfo.fCY = 100.f;
    m_fSpeed = 6.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Monster/MinotaursIdle_L.bmp", L"MinotaursIdle_L");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Monster/MinotaursIdle_R.bmp", L"MinotaursIdle_R");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Monster/MinotaursFaint_L.bmp", L"MinotaursFaint_L");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Monster/MinotaursFaint_R.bmp", L"MinotaursFaint_R");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Monster/MinotaursCharge2.bmp", L"MinotaursCharge");
    m_pvecTile = CTileMgr::Get_Instance()->Get_TileVec();
    m_iHeadTileIdx = m_iTileIdx = Find_MyTileIdx();

    m_tInfo.fX = (*m_pvecTile)[m_iTileIdx]->Get_Info().fX;
    m_tInfo.fY = (*m_pvecTile)[m_iTileIdx]->Get_Info().fY - 24.f;
    m_pTarget = GET_PLAYER;
    m_eDir = DIR_LEFT;
    m_ePrevDir = DIR_LEFT;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 100;
    m_tFrame.dwTime = GetTickCount64();

    m_iMoney = 200;
    m_pImgKey = L"MinotaursIdle_L";
    m_fJumpPower = 9.5f;
    Get_TileX();
    Get_TileY();
    m_eRender = RENDER_GAMEOBJECT;
    m_iMaxHP = 5;
    m_iHP = 5;
    m_iDamage = 6;
    m_HP_UI.Set_Target(this);
    m_HP_UI.Initialize();
    CObjMgr::Get_Instance()->Add_Object(OBJ_UI, &m_HP_UI);
}

int CTauren::Update()
{
    if (m_bDead || m_iHP == 0)
    {
        CBeatMgr::Get_Instance()->Plus_BeatCombo();
        CSoundMgr::Get_Instance()->StopSound(SOUND_MONHIT1);
        CSoundMgr::Get_Instance()->StopSound(SOUND_MONDEATH1);
        CSoundMgr::Get_Instance()->PlaySound(L"en_minotaur_death.wav", SOUND_MONDEATH1, 0.3f);
        static_cast<CStair*>(CObjMgr::Get_Instance()->Get_LastStair())->Set_IsClosed(false);
        return OBJ_DEAD;
    }

    if (m_eDir == DIR_LEFT)
        m_ePrevDir = DIR_LEFT;
    else if (m_eDir == DIR_RIGHT)
        m_ePrevDir = DIR_RIGHT;
    if (m_bPlayerFound)
    {
        if (BEATMGR->Get_ObjectAbleToMove() == true)
        {
            if (m_eCurState == FAINT_ACT && m_iBumped < 2) // 3턴 이동 x 2턴 faint모션 1턴 일어나기
            {
                ++m_iBumped;
                if (m_iBumped == 2)
                {
                    m_eCurState = IDLE_ACT;
                    m_iBumped = 0;
                    m_tFrame.iFrameStart = 0;
                    if (m_ePrevDir == DIR_LEFT)
                        m_pImgKey = L"MinotaursIdle_L";
                    else
                        m_pImgKey = L"MinotaursIdle_R";
                    return OBJ_NOEVENT;
                }
                CTileMgr::Get_Instance()->Remove_TileObject(m_iTileIdx, TOBJ_ENTITY);
                CTileMgr::Get_Instance()->Set_TileObject(m_iHeadTileIdx, TOBJ_ENTITY, this);
                m_iHeadTileIdx = m_iTileIdx = Find_MyTileIdx();
                if (m_ePrevDir == DIR_LEFT)
                    m_pImgKey = L"MinotaursFaint_L";
                else
                    m_pImgKey = L"MinotaursFaint_R";

                m_tFrame.iFrameStart = 0;
                //m_iTileIdx = 
                return OBJ_NOEVENT;
            }
            else if (m_eCurState == DASH_ACT)
            {
                m_tFrame.iFrameStart = 0;
                if (m_ePrevDir == DIR_RIGHT)
                    m_tFrame.iFrameStart = 1;
                m_pImgKey = L"MinotaursCharge";
            }
            else if (m_eCurState == IDLE_ACT)
            {
                m_iBumped = 0;
                m_tFrame.iFrameStart = 0;
                if (m_ePrevDir == DIR_LEFT)
                    m_pImgKey = L"MinotaursIdle_L";
                else
                    m_pImgKey = L"MinotaursIdle_R";
                m_eCurState = IDLE_ACT;
            }
            else
            {
                m_iBumped = 0;
                m_tFrame.iFrameStart = 0;
                if (m_ePrevDir == DIR_LEFT)
                    m_pImgKey = L"MinotaursIdle_L";
                else
                    m_pImgKey = L"MinotaursIdle_R";
                m_eCurState = IDLE_ACT;
            }
            m_iTileIdx = Find_MyTileIdx();
            if (m_pTarget != nullptr)
            {
                if (m_eCurState != DASH_ACT)
                {
                    Find_Player();
                    if (m_eDir == DIR_LEFT)
                        m_ePrevDir = DIR_LEFT;
                    else if (m_eDir == DIR_RIGHT)
                        m_ePrevDir = DIR_RIGHT;
                    int iPHTileIdx = static_cast<CPlayer*>(m_pTarget)->Get_TileIdx();
                    int iPlayerX = iPHTileIdx % TILEX;
                    int iPlayerY = iPHTileIdx / TILEX;
                    if (m_iTileX == iPlayerX || m_iTileY == iPlayerY)
                    {
                        m_eCurState = DASH_ACT;
                        CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT4);
                        CSoundMgr::Get_Instance()->PlaySound(L"en_minotaur_charge.wav", SOUND_EFFECT4, 0.3f);

                        CTauren::Update();
                        return OBJ_NOEVENT;
                    }
                }
            }
            if (m_eDir == DIR_LEFT)
                m_ePrevDir = DIR_LEFT;
            else if (m_eDir == DIR_RIGHT)
                m_ePrevDir = DIR_RIGHT;
            if (Can_Move())
            {
                m_bMove = true;
            }
            else
            {
                float	fHeadX(0.f), fHeadY(0.f);
                fHeadX = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fX;
                fHeadY = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fY;
                CObj* pHeadWall = CTileMgr::Get_Instance()->Is_Wall_Exist(fHeadX, fHeadY);

                int iPHTileIdx = static_cast<CPlayer*>(m_pTarget)->Get_HeadTileIdx();
                if (iPHTileIdx == m_iHeadTileIdx)
                {
                    m_eCurState = FAINT_ACT;
                    if (m_ePrevDir == DIR_LEFT)
                        m_pImgKey = L"MinotaursFaint_L";
                    else
                        m_pImgKey = L"MinotaursFaint_R";
                }
                if (pHeadWall != nullptr)		// 벽 검사
                {
                    if (m_eCurState == DASH_ACT)
                    {
                        CTileMgr::Get_Instance()->Break_Wall(pHeadWall, nullptr);
                        CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT4);
                        CSoundMgr::Get_Instance()->PlaySound(L"en_minotaur_wallimpact.wav", SOUND_EFFECT4, 0.3f);

                        m_eCurState = FAINT_ACT;
                        if (m_ePrevDir == DIR_LEFT)
                            m_pImgKey = L"MinotaursFaint_L";
                        else
                            m_pImgKey = L"MinotaursFaint_R";

                    }
                    else if (m_eCurState == IDLE_ACT)
                    {
                        CTileMgr::Get_Instance()->Break_Wall(pHeadWall, nullptr);
                    }
                }
                m_iHeadTileIdx = m_iTileIdx;
            }

            //BEATMGR->Set_ObjectAbleToMove(false);
        }

        if (m_eCurState == FAINT_ACT)
        {
            m_bMove = false;
        }
        Jumping();
    }
    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CTauren::Late_Update()
{
    if (m_eCurState == DASH_ACT)
        return;
    
    int iDistance = abs(m_pTarget->Get_TileX() - Get_TileX()) + abs(m_pTarget->Get_TileY() - Get_TileY());
	if (m_bPlayerFound == false)
    {
        if (iDistance <= 10)
        {
            m_bPlayerFound = true;
			CSoundMgr::Get_Instance()->PlaySound(L"en_minotaur_cry.wav", SOUND_EFFECT3, 0.2f);
        }
    }
    __super::Move_Frame();
}

void CTauren::Render(HDC hDC)
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

void CTauren::Release()
{
    CObjMgr::Get_Instance()->Delete_Object(OBJ_UI, &m_HP_UI);
}

void CTauren::Play_HitSound()
{
    CSoundMgr::Get_Instance()->StopSound(SOUND_MONHIT1);
    CSoundMgr::Get_Instance()->PlaySound(L"en_minotaur_hit_01.wav", SOUND_MONHIT1, 0.2f);
}
