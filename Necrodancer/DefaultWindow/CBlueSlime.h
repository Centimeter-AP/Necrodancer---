#pragma once
#include "CMonster.h"
class CBlueSlime : public CMonster
{
public:
    CBlueSlime()
    : m_iSelectedIndex{0,0}, m_eCurState(BEFORE_ACT)
    {}
    virtual ~CBlueSlime() { Release(); }
public:
    virtual void Initialize() override;
    virtual int  Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void     Play_HitSound();

private:
    enum ACTSTATE { BEFORE_ACT, AFTER_ACT, END_ACT };
    ACTSTATE    m_eCurState;
    int         m_iSelectedIndex[2];
};

