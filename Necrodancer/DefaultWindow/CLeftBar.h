#pragma once
#include "CObj.h"
class CLeftBar :
    public CObj
{
public:
    CLeftBar() {}
    virtual ~CLeftBar() { Release(); }
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

