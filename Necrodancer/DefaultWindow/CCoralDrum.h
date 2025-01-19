#pragma once
#include "CCoralInst.h"
class CCoralDrum :
    public CCoralInst
{
public:
    CCoralDrum(){}
    virtual ~CCoralDrum() { Release(); }
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

private:

};

