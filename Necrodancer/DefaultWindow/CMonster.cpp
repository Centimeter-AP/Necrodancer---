#include "pch.h"
#include "CMonster.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
    Release();
}

void CMonster::Initialize()
{
    m_tInfo.fCX = 300.f;
    m_tInfo.fCY = 300.f;
    m_fSpeed = 3.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster.bmp", L"Monster");

    m_pImgKey = L"Monster";

    m_eRender = RENDER_GAMEOBJECT;
}

int CMonster::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

   
    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
 
}

void CMonster::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

    int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    GdiTransparentBlt(hDC,			// 복사 받을 DC
        m_tRect.left + iScrollX,	// 복사 받을 위치 좌표 X, Y	
        m_tRect.top + iScrollY,
        (int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
        (int)m_tInfo.fCY,
        hMemDC,						// 복사할 이미지 DC	
        0,							// 비트맵 출력 시작 좌표(Left, top)
        0,
        (int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
        (int)m_tInfo.fCY,
        RGB(255, 255, 255));		// 제거할 색상
}

void CMonster::Release()
{
}
