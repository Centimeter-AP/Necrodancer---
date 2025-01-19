#pragma once
#include "CObj.h"
class CPlayerItemUI :
    public CObj
{
public:
    CPlayerItemUI(): m_iItemPosX(0) {}
    virtual ~CPlayerItemUI() {}
public:
    void Initialize()   PURE;
    int  Update()       PURE;
    void Late_Update()  PURE;
    void Render(HDC hDC)PURE;
    void Release()      PURE;
protected:
    int     m_iItemPosX;
};

