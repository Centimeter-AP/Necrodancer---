#pragma once
#include "CHealing.h"
class CApple :
    public CHealing
{
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
public:
	virtual void Use_Item() override;
};

