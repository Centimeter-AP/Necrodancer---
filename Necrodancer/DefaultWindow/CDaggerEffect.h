#pragma once
#include "CEffect.h"
class CDaggerEffect :
    public CEffect
{
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

// 48 48 