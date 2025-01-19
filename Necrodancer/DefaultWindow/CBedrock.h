#pragma once
#include "CWall.h"
class CBedrock :
    public CWall
{
public:
    CBedrock();
    ~CBedrock();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

