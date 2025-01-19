#pragma once
#include "CObj.h"
class CItem : public CObj
{
public:
	CItem() : m_iAnimationOffsetY(0), m_iImgPosX(0), m_eItemType(ITEM_END),
        m_bOnMap(false), m_bUsing(false), m_iShowFrame(20),
        m_iIdleFrame(100), m_iFrameTicker(0), m_bIsPlayerOnTile(false),
		m_iPrice(0), m_bIsSelling(false)
    {}
	virtual ~CItem() { }
public:
    virtual void Initialize()       PURE;
    virtual int  Update()           PURE;
    virtual void Late_Update()      PURE;
    virtual void Render(HDC hDC)    PURE;
    virtual void Release()          PURE;

public:
    void        Set_OnMap(bool _bOnMap) { m_bOnMap = _bOnMap; }
    void        Set_Using(bool _bUsing) { m_bUsing = _bUsing; }
    void        Set_FrameTickerZero() { m_iFrameTicker = 0; }
	void        Set_NeedGold(int _iNeedGold) { m_iPrice = _iNeedGold; }
	void        Set_IsSelling(bool _bIsSelling) { m_bIsSelling = _bIsSelling; }
	void        Set_Price(int _iPrice) { m_iPrice = _iPrice; }  
	bool        Get_IsSelling() { return m_bIsSelling; }
	int         Get_Price() { return m_iPrice; }
    bool        Get_OnMap() { return m_bOnMap; }
    bool        Get_Using() { return m_bUsing; }
    int         Get_TileIdx() { return m_iTileIdx; }
    ITEMLIST    Get_ItemType() { return m_eItemType; }
    int         Get_ImgPosX() { return m_iImgPosX; }
	auto&       Get_ImgKey() { return m_pImgKey; }

    void        Find_TileIdx_OnMap();
    void        Find_Player_OnSameTile();
    void        Draw_Price(HDC hDC);
	void        Play_PurchaseSound();

protected:
    int         m_iAnimationOffsetY;
    int         m_iImgPosX;
    bool        m_bOnMap;
    bool        m_bUsing;
    bool        m_bIsPlayerOnTile;
    int         m_iShowFrame;
    int         m_iIdleFrame;
    int         m_iFrameTicker;
    ITEMLIST    m_eItemType;
    int         m_iPrice;
    bool        m_bIsSelling;
};

