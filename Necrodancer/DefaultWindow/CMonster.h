#pragma once
#include "CObj.h"
#include "CMonsterHP.h"
class CMonster : public CObj
{
public:
    CMonster();
    virtual ~CMonster();

public:
    virtual void Initialize() override;
    virtual int  Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    void         Find_Player();
    void         Set_FirstTileIdx() { m_iHeadTileIdx = m_iTileIdx = Find_MyTileIdx(); }

    void        Jumping();
    void        BossMove();
    void        BossInstMove();
    bool        Can_Move();

    virtual void     Play_HitSound() PURE;
    void        Attack_Effect();

protected:
    enum MONSTATE { MON_IDLE, MON_AGGRO, MON_ATTACK, MON_END };

    CMonsterHP  m_HP_UI;

    vector<CObj*>* m_pvecTile;
    //int         m_iCurTileIdx;
    int         m_iHeadTileIdx;
    float       m_fJumpPower;
    float       m_fTime;
    bool        m_bMove;
    float       m_fShadowY;
    bool        m_bCanChangeDir;
    bool        m_bPlayerFound;
    int         m_iDamage;

    int         m_iMoney;
    int         m_iImgCX;
    int         m_iImgCY;
};
