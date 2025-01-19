#pragma once

class CObj;
class CWallMgr
{
private:
	friend class CTileMgr;
	CWallMgr() {}
	virtual ~CWallMgr() {}

public:
	void Initialize();
	int  Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	void			Picking_Wall(POINT pt, int iDrawID, int iOption);
	vector<CObj*>*	Get_WallVec() { return &m_vecWall; }

public:
	static CWallMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CWallMgr;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CWallMgr* m_pInstance;

	vector<CObj*>	m_vecWall;

};

