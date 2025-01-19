#pragma once
#include "CStage.h"
class CLobby : public CStage
{
public:
	CLobby();
	virtual ~CLobby();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

