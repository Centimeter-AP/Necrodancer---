#include "pch.h"
#include "CPlayerArmorUI.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CBeatMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CItem.h"

void CPlayerArmorUI::Initialize()
{
    m_tInfo = { 190.f, 125.f, 60.f, 66.f };
    m_pImgKey = L"armorgi";
    m_pTarget = CObjMgr::Get_Instance()->Get_Player();
    m_pCurArmor = nullptr;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/UI/UI_Armor.bmp", L"UI_Armor");
    m_eRender = RENDER_UI;
}

int CPlayerArmorUI::Update()
{
    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CPlayerArmorUI::Late_Update()
{
    m_pCurArmor = static_cast<CPlayer*>(m_pTarget)->Get_CurArmor();

    if (m_pCurArmor == nullptr)
        m_bHasItem = false;
    else
        m_bHasItem = true;
}

void CPlayerArmorUI::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"UI_Armor");
    HDC		hMemDCCur = CBmpMgr::Get_Instance()->Find_Image(L"armor_gi");

    if (m_bHasItem)
    {
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
            m_tRect.left + 6,		// 복사 받을 위치 좌표 X, Y	
            m_tRect.top + 14,
            48,							// 복사 받을 이미지의 가로, 세로
            48,
            hMemDCCur,								// 복사할 이미지 DC	
            0,	// 비트맵 출력 시작 좌표(Left, top)
            0,
            48,							// 복사할 이미지의 가로, 세로
            48,
            RGB(255, 0, 255));					// 제거할 색상
    }


}

void CPlayerArmorUI::Release()
{
}
