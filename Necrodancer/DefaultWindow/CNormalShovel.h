#pragma once
#include "CShovel.h"
class CNormalShovel :
    public CShovel
{
public:
    CNormalShovel() {}
    virtual ~CNormalShovel() {}
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

