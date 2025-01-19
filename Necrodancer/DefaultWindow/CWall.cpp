#include "pch.h"
#include "CWall.h"

CWall::CWall()
    : m_iPowerNeeded(0), m_iImgPosX(0), m_iImgPosY(0), m_enWallType(WALL_END)
{
    m_pImgKey = L"Wall";
    //ZeroMemory(&m_iWallNumber, sizeof(m_iWallNumber));
}

CWall::~CWall()
{
}
