#pragma once
#include "CCoralInst.h"
class CCoralBrass :
    public CCoralInst
{
public:
    CCoralBrass() {}
    virtual ~CCoralBrass() { Release(); }
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

private:

};

