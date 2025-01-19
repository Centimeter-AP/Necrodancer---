#pragma once

#include "CObj.h"

class CTile :   public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	int			Get_DrawID() { return m_iDrawID; }
	int			Get_Option() { return m_iOption; }
	array<CObj*, TOBJ_END>&	Get_TileObj() { return m_pObject; }

	void		Set_TileObj(TILEOBJECT _OBJID, CObj* _Obj) { m_pObject[_OBJID] = _Obj; }
	void		Remove_TileObj(TILEOBJECT _OBJID) { m_pObject[_OBJID] = nullptr; }
	void		Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID;  }
	void		Set_Option(int _iOption) { m_iOption = _iOption; }

public:
	void		Initialize() override;
	int			Update() override;
	void		Late_Update() override;
	void		Render(HDC hDC) override;
	void		Release() override;

protected:
	int		m_iDrawID; 
	int		m_iOption;
	array<CObj*, TOBJ_END>	m_pObject;
};

