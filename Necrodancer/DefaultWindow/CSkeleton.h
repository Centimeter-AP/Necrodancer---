#pragma once
#include "CMonster.h"
class CSkeleton : public CMonster
{
public:
    CSkeleton(): m_eCurState(AFTER_ACT), m_bAttacked(true), m_iActMotionOffset(192), m_iBeforeAct(0){}
    virtual ~CSkeleton() { Release(); }
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void     Play_HitSound();
private:
    enum ACTSTATE{BEFORE_ACT, AFTER_ACT, END_ACT};
    ACTSTATE    m_eCurState;
    bool        m_bAttacked;
    int         m_iActMotionOffset;
    int         m_iBeforeAct;
};

