#pragma once
#include "CWall.h"
class CStoneWall : public CWall
{
public:
	CStoneWall();
	virtual ~CStoneWall();
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

