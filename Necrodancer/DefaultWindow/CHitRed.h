#pragma once
#include "CObj.h"
class CHitRed :
    public CObj
{
public:
	CHitRed() : m_iHitFrameCount(0), m_bIsHit(true)
    {}
	virtual ~CHitRed(){}
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    int     m_iHitFrameCount;
    bool    m_bIsHit;
};

