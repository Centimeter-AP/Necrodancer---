#pragma once
#include "CPlayerItemUI.h"
class CPlayerShovelUI : public CPlayerItemUI
{
public:
	CPlayerShovelUI() : m_pCurShov(nullptr) {}
	~CPlayerShovelUI() { Release(); }

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	CObj* m_pCurShov;
};

