#pragma once
#include "CEffect.h"
class CMonsterEffect : public CEffect
{
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};
// 54, 48 
