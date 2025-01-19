#pragma once
#include "CMonster.h"
class CDummy :  public CMonster
{
public:
    virtual void Initialize() override;
    virtual int  Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual void Play_HitSound();
};

