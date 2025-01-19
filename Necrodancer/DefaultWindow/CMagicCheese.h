#pragma once
#include "CHealing.h"
class CMagicCheese :
    public CHealing
{
public:
    CMagicCheese() : m_bSecretRevealed(false){}
	virtual ~CMagicCheese() {}
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    virtual void Use_Item() override;

private:
	bool m_bSecretRevealed;
};

