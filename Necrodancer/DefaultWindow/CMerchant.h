#pragma once
#include "CObj.h"
class CMerchant : public CObj
{
public:
	CMerchant() : m_bIsSinging(false) {}
	virtual ~CMerchant() { Release(); }
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	bool m_bIsSinging;
};

