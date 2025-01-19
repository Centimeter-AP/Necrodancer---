#pragma once
#include "CStage.h"
class CStageOne : public CStage
{
public:
	CStageOne();
	virtual ~CStageOne();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
private:
	CObj* m_pBoss;
	bool m_bSecretOpened;
};

