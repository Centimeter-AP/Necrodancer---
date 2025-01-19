#pragma once
#include "CObj.h"
class CMonsterHP : public CObj
{
public:
	CMonsterHP() {}
	virtual ~CMonsterHP() {}

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void Set_Target(CObj* _rhs);
};

