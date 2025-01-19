#pragma once
#include "CObj.h"
class CMissInputText : public CObj
{
public:
	CMissInputText() : m_iMovingOffsetY(0) {}
	virtual ~CMissInputText() { Release(); }

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	int m_iMovingOffsetY;
};

