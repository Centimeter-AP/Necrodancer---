#pragma once

#include "Define.h"
#include "CObj.h"

class CItem;
class CObjMgr
{
private:
	CObjMgr();
	CObjMgr(const CObjMgr& rhs) = delete;
	CObj operator =(CObj& rObj) = delete;
	~CObjMgr();
public:
	CObj* Get_Player()		{ return m_ObjList[OBJ_PLAYER].front(); }
	auto& Get_MonsterList()	{ return m_ObjList[OBJ_MONSTER];	}
	CObj* Get_FirstMonster() { return m_ObjList[OBJ_MONSTER].front(); }
	CObj* Get_LastMonster() { return m_ObjList[OBJ_MONSTER].back(); }
	CObj* Get_LastItem()	{ return m_ObjList[OBJ_ITEM].back(); }
	CObj* Get_LastBar()		{ return m_ObjList[OBJ_UI].back(); }
	CObj* Get_LastStair()   { return m_ObjList[OBJ_STAIR].back(); }
	CObj* Get_LastEffect()  { return m_ObjList[OBJ_EFFECT].back(); }
	CObj* Get_LastGold()	{ return m_ObjList[OBJ_GOLD].back(); }
	CObj* Get_Target(OBJID eID, CObj* pDst);

	CObj* Is_Item_Exist(float fx, float fy);
	CObj* Is_Item_Exist(int _iTileIdx);

	CObj* Is_Monster_Exist(float fx, float fy);
	CObj* Is_Monster_Exist(int _iTileIdx);

	void	Get_Item(CItem* _pItem);
	bool	Find_ifExist(OBJID eID, CObj* pObj);
	bool	Check_IsPlayerEmpty() { return m_ObjList[OBJ_PLAYER].empty(); }

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	void		Delete_ID(OBJID eID);
	void		Delete_Object(OBJID eID, CObj* pObj);
	void		Delete_Map_Item();

public:
	static CObjMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}

	static void		DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	list<CObj*>		m_ObjList[OBJ_END];
	list<CObj*>		m_RenderList[RENDER_END];

	static CObjMgr* m_pInstance;


};

