#pragma once
#include "CObj.h"
class CBossCutscene : public CObj
{
public:
	CBossCutscene() :m_iMovingOffsetTop(0), m_iMovingOffsetBottom(0), m_iMovingOffsetMid(0)
	, m_bCanMoveTop(true), m_bCanMoveBottom(false), m_bCanMoveMid(true)
	, m_bIsAppear(true), m_bIsDisappear(false), m_iDisappearTimer(0)
	{}
	virtual ~CBossCutscene() {}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	int	m_iMovingOffsetTop;
	int	m_iMovingOffsetMid;
	int m_iMovingOffsetBottom;
	bool m_bCanMoveTop;
	bool m_bCanMoveMid;
	bool m_bCanMoveBottom;
	bool m_bIsAppear;
	bool m_bIsDisappear;
	int  m_iDisappearTimer;
};
