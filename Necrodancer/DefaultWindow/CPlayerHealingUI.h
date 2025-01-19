#pragma once
#include "CPlayerItemUI.h"
class CPlayerHealingUI :
    public CPlayerItemUI
{
public:
	CPlayerHealingUI() :m_bHasItem(false), m_eItemName(ITEMNAME_END), m_pCurHealingItem(nullptr)
    {}
    virtual ~CPlayerHealingUI() {}
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
	CObj* m_pCurHealingItem;
    bool m_bHasItem;
    enum ITEMNAME {NORMALCHEESE, MAGICCHEESE, ITEMNAME_END};
    ITEMNAME  m_eItemName;
};

