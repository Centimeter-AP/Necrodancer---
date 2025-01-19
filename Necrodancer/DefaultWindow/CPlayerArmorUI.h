#pragma once
#include "CPlayerItemUI.h"
class CPlayerArmorUI :
    public CPlayerItemUI
{
public:
    CPlayerArmorUI() {}
	virtual ~CPlayerArmorUI() {}
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    CObj* m_pCurArmor;
    bool m_bHasItem;
};

