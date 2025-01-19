#pragma once
#include "CMonster.h"
class CTauren : public CMonster
{
public:
    CTauren()
    : m_eCurState(IDLE_ACT)
		, m_iBumped(0), m_ePrevDir(DIR_LEFT)
    {}
    virtual ~CTauren() { Release(); }

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Play_HitSound();

private:
    enum ACTSTATE { IDLE_ACT, DASH_ACT, FAINT_ACT, END_ACT };
    ACTSTATE    m_eCurState;
    int         m_iBumped;
    int         m_iActMotionOffset;
    int         m_iBeforeAct;
    DIRECTION   m_ePrevDir;
};

