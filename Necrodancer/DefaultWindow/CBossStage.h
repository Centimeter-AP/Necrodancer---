#pragma once
#include "CStage.h"
class CBossStage : public CStage
{
public:
	CBossStage();
	virtual ~CBossStage();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	bool m_bPlayerEntered;
	bool m_bPlayerEnteredCheck;

	bool m_bPlayerCleared;
	bool m_bPlayerClearedCheck;

	bool m_bCutscene;
	bool m_bCutsceneCheck;
};