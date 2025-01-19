#pragma once
#include "CCoralInst.h"
class CCoralPiano :
    public CCoralInst
{
public:
    CCoralPiano() {}
    virtual ~CCoralPiano() { Release(); }
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

private:

};

