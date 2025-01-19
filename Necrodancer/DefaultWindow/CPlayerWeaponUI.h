#pragma once
#include "CPlayerItemUI.h"
class CPlayerWeaponUI :
    public CPlayerItemUI
{
public:
    CPlayerWeaponUI() : m_pCurWeapon(nullptr){}
    virtual ~CPlayerWeaponUI() { Release(); }
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    CObj* m_pCurWeapon;
};

