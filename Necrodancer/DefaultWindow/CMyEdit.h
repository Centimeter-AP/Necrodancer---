#pragma once

#include "CScene.h"

class CMyEdit :   public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	void Initialize()		override;
	int  Update()			override;
	void Late_Update()		override;
	void Render_InfoText(HDC hDC);
	void Render(HDC hDC)	override;
	void Release()			override;

private:
	void	Key_Input();


private:
	TILEOPTIONID	m_enType;
	int		m_iNum;
};

