#include "pch.h"
#include "CPlayerWeaponUI.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CBeatMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CItem.h"


void CPlayerWeaponUI::Initialize()
{
    m_tInfo = { 120.f, 125.f, 60.f, 66.f };
    m_pImgKey = L"Dagger";
    m_pTarget = CObjMgr::Get_Instance()->Get_Player();
    m_pCurWeapon = static_cast<CPlayer*>(m_pTarget)->Get_CurWeapon();

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/UI/UI_Weapon.bmp", L"UI_Weapon");
    m_eRender = RENDER_UI;
}

int CPlayerWeaponUI::Update()
{
    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CPlayerWeaponUI::Late_Update()
{
    m_pCurWeapon = static_cast<CPlayer*>(m_pTarget)->Get_CurWeapon();

    m_iItemPosX = static_cast<CItem*>(m_pCurWeapon)->Get_ImgPosX();
}

void CPlayerWeaponUI::Render(HDC hDC)
{

    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"UI_Weapon");
    HDC		hMemDCCurShov = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

    GdiTransparentBlt(hDC,					// 복사 받을 DC
        m_tRect.left,			// 복사 받을 위치 좌표 X, Y	
        m_tRect.top,
        (int)m_tInfo.fCX,							// 복사 받을 이미지의 가로, 세로
        (int)m_tInfo.fCY,
        hMemDC,								// 복사할 이미지 DC	
        0,	// 비트맵 출력 시작 좌표(Left, top)
        0,
        (int)m_tInfo.fCX,							// 복사할 이미지의 가로, 세로
        (int)m_tInfo.fCY,
        RGB(255, 0, 255));					// 제거할 색상

    GdiTransparentBlt(hDC,					// 복사 받을 DC
        m_tRect.left + ((int)m_tInfo.fCX - (int)m_pCurWeapon->Get_Info().fCX)/2,			// 복사 받을 위치 좌표 X, Y	
        m_tRect.top + ((int)m_tInfo.fCY - (int)m_pCurWeapon->Get_Info().fCY) / 2 + 6,
        (int)m_pCurWeapon->Get_Info().fCX,							// 복사 받을 이미지의 가로, 세로
        (int)m_pCurWeapon->Get_Info().fCY,
        hMemDCCurShov,								// 복사할 이미지 DC	
        m_iItemPosX,	// 비트맵 출력 시작 좌표(Left, top)
        0,
        (int)m_pCurWeapon->Get_Info().fCX,							// 복사할 이미지의 가로, 세로
        (int)m_pCurWeapon->Get_Info().fCY,
        RGB(255, 0, 255));					// 제거할 색상

}

void CPlayerWeaponUI::Release()
{
}
