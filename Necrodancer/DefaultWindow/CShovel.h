#pragma once
#include "CItem.h"
class CShovel :
    public CItem
{
public:
    CShovel() : m_iPower(0){}
    virtual ~CShovel() {}
public:
    virtual void Initialize()       PURE;
    virtual int Update()            PURE;
    virtual void Late_Update()      PURE;
    virtual void Render(HDC hDC)    PURE;
    virtual void Release()          PURE;

public:
    int     Get_Power() { return m_iPower; }

protected:
    void    Get_RenderPos();

protected:
    int     m_iPower;
};

