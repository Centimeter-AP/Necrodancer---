#pragma once
#include "CEffect.h"
class CSplash : public CEffect
{
public:
	CSplash() {}
	virtual ~CSplash() {}
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

