#include "pch.h"
#include "CPlayerMoney.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CBeatMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"

void CPlayerMoney::Initialize()
{

    m_tInfo = { (float)WINCX - 100.f, 125.f, 40.f, 40.f };
    m_pImgKey = L"Gold";
	m_iMoney = static_cast<CPlayer*>(GET_PLAYER)->Get_Money();

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/UI/Gold.bmp", L"Gold");
    m_eRender = RENDER_UI;
}

int CPlayerMoney::Update()
{
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayerMoney::Late_Update()
{
	m_iMoney = static_cast<CPlayer*>(GET_PLAYER)->Get_Money();

}

void CPlayerMoney::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

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
        RGB(255, 0, 255));


	HFONT hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("NecroSans"));
	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	// 글씨 색상 설정
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT);

    TCHAR szText[32];
    wsprintf(szText, L"x%d", m_iMoney);
    TextOut(hDC, m_tRect.left + 50, m_tRect.top + 10, szText, lstrlen(szText));


	// 폰트 해제 및 텍스트 정렬 원래대로 복구
	SelectObject(hDC, hOldFont);
	DeleteObject(hFont);








}

void CPlayerMoney::Release()
{
}
