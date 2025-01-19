#pragma once
#include "CObj.h"
class CPlayerMoney :
    public CObj
{
public:
    CPlayerMoney():m_iMoney(0) {}
    virtual ~CPlayerMoney() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
	int m_iMoney;
};

