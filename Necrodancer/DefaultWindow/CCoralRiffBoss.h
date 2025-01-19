#pragma once
#include "CMonster.h"
class CCoralRiffBoss : public CMonster
{
public:
    CCoralRiffBoss() : m_iBeatPassed(0), m_eCurState(AFTER_ACT), m_iPhasePassed(0)
        , m_bAttacked(true), m_iBeforeAct(0), m_ibMovePhase(false), m_iShakeAnimation(5) 
        , m_iTeleportPos{ 463 ,471, 718, 726 }
    {}                   
    virtual ~CCoralRiffBoss() { Release(); }
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void     Play_HitSound();
    void        Teleport_Hit();

public:
    void        Set_Inst(CObj* _pInst) { m_vecInstrument.push_back(_pInst); }
    void        Set_Phase(int _i) { m_iPhasePassed = _i; }

    void        Inst_Phase();
    void        Move_Phase();
    void        Set_InstTilePos();

private:
    enum ACTSTATE { BEFORE_ACT, AFTER_ACT, END_ACT };
    ACTSTATE    m_eCurState;
    bool        m_bAttacked;
    int         m_iBeforeAct;
    bool        m_ibMovePhase;

    int         m_iBeatPassed;
    int         m_iPhasePassed;

    int         m_iShakeAnimation;
    int         m_iTeleportPos[4];

    vector<CObj*>      m_vecInstrument;
};

