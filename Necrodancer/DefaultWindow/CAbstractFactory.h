#pragma once

#include "CObj.h"
#include "CItem.h"
#include "CObjMgr.h"
#include "CTileMgr.h"
#include "CMonster.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {};

public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(float _fX, float _fY, float _fAngle = 0.f)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_TileIdx(pObj->Find_MyTileIdx());
		if(0.f != _fAngle)
			pObj->Set_Angle(_fAngle);

		return pObj;
	}
	static CObj* Create(int _iTileIdx)
	{
		CObj* pObj = new T;
		float fX = float((_iTileIdx % TILEX) * 48 + 24);
		float fY = float((_iTileIdx / TILEX) * 48 + 24);
		pObj->Set_Pos(fX, fY);
		pObj->Initialize();
		pObj->Set_TileIdx(_iTileIdx);

		return pObj;
	}

	static CObj* Create_Monster(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Initialize();
		static_cast<CMonster*>(pObj)->Set_FirstTileIdx();

		return pObj;
	}
	static CObj* Create(INFO	_info)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_info.fX, _info.fY);

		return pObj;
	}
	static CObj* Create_Item(bool _isOnMap, float _fX = 0.f, float _fY = 0.f)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		if (_isOnMap)
			static_cast<CItem*>(pObj)->Set_OnMap(_isOnMap);
		int iTileIdx = ((int)_fY / TILECY) * TILEX + ((int)_fX / TILECX);
		pObj->Set_Pos(
			(*(CTileMgr::Get_Instance()->Get_TileVec()))[iTileIdx]->Get_Info().fX,
			(*(CTileMgr::Get_Instance()->Get_TileVec()))[iTileIdx]->Get_Info().fY - 24.f);
		//pObj->Set_Target(CObjMgr::Get_Instance()->Get_Player());
		return pObj;
	}
	static CObj* Create_Item(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		dynamic_cast<CItem*>(pObj)->Set_OnMap(true);
		pObj->Set_Pos(_fX, _fY);
		return pObj;
	}
	static CObj* Create_Bar(bool _isLeft)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		if (_isLeft == false)
		{
			pObj->Set_SpeedReverse();
			pObj->Set_Pos((float)WINCX, (float)WINCY - 145.f);
		}
		return pObj;
	}

};

