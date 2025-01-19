#pragma once
#include "CWeapon.h"
class CDagger : public CWeapon
{
public:
	CDagger() {}
	virtual ~CDagger() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

