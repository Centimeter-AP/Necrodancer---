#pragma once
#include "CArmor.h"
class CArmorGi :
    public CArmor
{
    // CArmor을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

