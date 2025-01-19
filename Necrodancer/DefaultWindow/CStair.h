#pragma once
#include "CObj.h"
class CStair : public CObj
{
public:
	CStair(): m_iNextScene(SC_END), m_iIsClosed(0), m_bIsPlayerOnTile(false), m_bIsFirstTime(true){}
	virtual ~CStair() { Release(); }

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void	Set_NextScene(SCENEID _ID) { m_iNextScene = _ID; }
	void	Set_IsClosed(int _isclosed) { m_iIsClosed = _isclosed; }
	void	Interact_Stair();

private:
	int		m_iIsClosed;
	SCENEID	m_iNextScene;
	bool	m_bIsPlayerOnTile;
	bool	m_bIsFirstTime;
};

