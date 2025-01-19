#pragma once
#include "CWall.h"
class CDirtWall :
    public CWall
{
public:
    CDirtWall();
    virtual ~CDirtWall();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

