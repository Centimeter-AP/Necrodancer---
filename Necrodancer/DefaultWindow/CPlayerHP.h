#pragma once
#include "CObj.h"
class CPlayerHP :
    public CObj
{
public:
    CPlayerHP() {}
    ~CPlayerHP() {}
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};
