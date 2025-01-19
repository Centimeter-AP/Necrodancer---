#pragma once
#include "CObj.h"
#include "CShield.h"
#include "CScrewBullet.h"
#include "CGuideBullet.h"
#include "CTileMgr.h"

class CItem;
class CPlayer :    public CObj
{
public:
    enum STATE { IDLE, WALK, ATTACK, HIT, DEAD, END };

public:
    CPlayer();
    virtual ~CPlayer();

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    //int          Get_CurTileIdx() { return m_iCurTileIdx; }
    int          Get_HeadTileIdx() { return m_iHeadTileIdx; }
    CObj*        Get_CurShovel() { return m_Itemlist[ITEM_SHOVEL].front(); }
    CObj*        Get_CurWeapon() { return m_Itemlist[ITEM_WEAPON].front(); }
    CObj*        Get_CurHealing() { if (!m_Itemlist[ITEM_HEAL].empty()) return m_Itemlist[ITEM_HEAL].front(); else return nullptr; }
    CObj*        Get_CurArmor() { if (!m_Itemlist[ITEM_ARMOR].empty()) return m_Itemlist[ITEM_ARMOR].front(); else return nullptr; }
    list<CObj*>& Get_ItemSlot(int _iItemlist) {  return m_Itemlist[_iItemlist]; }
	int          Get_Money() { return m_iMoney; }

	void         Set_Money(int _iMoney) { m_iMoney += _iMoney; }
    void         Set_FirstTileIdx() { m_iHeadTileIdx = m_iTileIdx = Find_MyTileIdx(); }
    void         Set_PositionCorrect() {
        m_pvecTile = CTileMgr::Get_Instance()->Get_TileVec();
        m_iTileIdx = Find_MyTileIdx();
        m_tInfo.fX = (*m_pvecTile)[m_iTileIdx]->Get_Info().fX;
        m_tInfo.fY = (*m_pvecTile)[m_iTileIdx]->Get_Info().fY - 24.f;
        m_fShadowY = m_tInfo.fY - (m_tInfo.fCY * 0.5f) + 4.f;
    }
    void        Set_InWater(bool _isIn) { m_bInWater = _isIn; }
    bool        Get_InWater() { return m_bInWater; }
    void        Set_FullHP() { m_iHP = m_iMaxHP; }
    void        Attack_Effect();
	void        Set_Hit() { m_bHit = true; }
	void        Set_HasKey(bool _bHasKey) { m_bHasKey = _bHasKey; }
	bool        Get_HasKey() { return m_bHasKey; }  
	void        Set_MaxHP(int _iMaxHP) { m_iMaxHP += _iMaxHP; }

private:
    void        Key_Input();
    void        Jumping();
    void        Offset();

    CObj*       Create_Shield();
    void        Change_Motion();

    bool        Can_Move();

    void        Get_Item(CObj* _pItem);

    //void        Get_Item(CItem* _pItem);

private:
    float       m_fJumpX;
    float       m_fJumpY;
    float       m_fJumpPower;

    float       m_fTime;

    STATE       m_eCurState;
    STATE       m_ePreState;

    ULONGLONG   m_dwTempTick;
    
    //bool        m_bBeatCorrect;
    bool        m_bTemp;

    vector<CObj*>*	m_pvecTile;
    //int         m_iCurTileIdx;
    int         m_iHeadTileIdx;

    DIRECTION   m_ePrevDir;
    
    bool        m_bMove;

    float       m_fShadowY;
    int         m_iWaterTileOffset;
    bool        m_bInWater;

    bool        m_qltskrka;
    bool        m_bDebugMovable;
	bool    m_bHit;


    list<CObj*> m_Itemlist[ITEM_END];
    int         m_iMoney;

    bool        m_bHasKey;
    int         m_iArmorIdx;
};

