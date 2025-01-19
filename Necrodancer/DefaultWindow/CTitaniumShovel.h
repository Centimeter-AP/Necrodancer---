#pragma once
#include "CShovel.h"
class CTitaniumShovel : public CShovel
{
public:
    CTitaniumShovel() {}
    virtual ~CTitaniumShovel() {}
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

