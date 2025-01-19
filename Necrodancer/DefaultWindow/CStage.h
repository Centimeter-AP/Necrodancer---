#pragma once
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CMouse.h"

class CStage : public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

protected:
	bool	m_bBeatOne;
	int		m_iFrameCount;

};

