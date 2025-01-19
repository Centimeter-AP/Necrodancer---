#pragma once
#include "CItem.h"
class CWeapon : public CItem
{
public:
	CWeapon() : m_iDamage(0), m_eWeaponType(WEAPONTYPE_END){}
	virtual ~CWeapon(){}

public:
	virtual void Initialize()		PURE;
	virtual int Update()			PURE;
	virtual void Late_Update()		PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Release()			PURE;

	int		Get_Damage() { return m_iDamage; }
	void	Set_Damage(int _iDamage) { m_iDamage = _iDamage; }
public:
	enum WEAPONTYPE { DAGGER_TYPE, LONGSWORD_TYPE, BROADSWORD_TYPE, WEAPONTYPE_END };
	WEAPONTYPE	Get_WeaponType() { return m_eWeaponType; }

protected:
	int		m_iDamage;
	WEAPONTYPE m_eWeaponType;
	
};

