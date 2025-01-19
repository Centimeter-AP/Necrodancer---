#pragma once
#include "CObj.h"
class CWall : public CObj
{
public:
	CWall();
	virtual ~CWall();

public:
	virtual void Initialize()	 {}
	virtual int  Update() { return 0; }
	virtual void Late_Update()	 {}
	virtual void Render(HDC hDC) {}
	virtual void Release() {}

public:
	WALLTYPE	Get_WallType() { return m_enWallType; }
	void		Set_Hp(int _hp) { m_iHP += _hp; }
	void		Set_Damage(int _iShovPow, int _iDmg)
	{
		if (m_iPowerNeeded <= _iShovPow)
			m_iHP -= _iDmg;
		if (m_iHP <= 0)
		{
			m_iHP = 0;
			m_bDead = true;
		}
	}
	int			Get_PowerNeed() { return m_iPowerNeeded; }


protected:
	int		m_iPowerNeeded;		// ºÎ¼ö±â À§ÇØ ÇÊ¿äÇÑ Èû (»ð À§·Â ÃÖ¼ÒÄÆ)
	
	int		m_iImgPosX;
	int		m_iImgPosY;

	WALLTYPE	m_enWallType;
};

