#pragma once
#include "CWall.h"
class CDoor : public CWall
{
public:
	CDoor() {}
	virtual ~CDoor() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

};

