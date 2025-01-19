#pragma once
#include "CItem.h"
class CHealing :
    public CItem
{
public:
    virtual void Initialize()       PURE;
    virtual int  Update()           PURE;
    virtual void Late_Update()      PURE;
    virtual void Render(HDC hDC)    PURE;
    virtual void Release()          PURE;
public:
	virtual void Use_Item()         PURE;
};

