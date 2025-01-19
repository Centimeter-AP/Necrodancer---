#pragma once
#include "CWall.h"
class CVerticalDoor : public CWall
{
public:
	CVerticalDoor() {}
	virtual ~CVerticalDoor() {}
public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

