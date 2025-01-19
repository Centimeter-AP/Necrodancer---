#pragma once
#include "CItem.h"
class CGoldenKey : public CItem
{
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

};

