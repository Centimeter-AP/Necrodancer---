#pragma once
#include "CTile.h"
class CWaterTile : public CTile
{
public:
	CWaterTile();
	virtual ~CWaterTile();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
private:
	void Check_PlayerInWater();
};

