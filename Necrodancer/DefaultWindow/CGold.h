#pragma once
#include "CItem.h"
class CGold :
    public CItem
{
public:
	CGold() {}
	virtual ~CGold() {}
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
	int m_iGold;
};

