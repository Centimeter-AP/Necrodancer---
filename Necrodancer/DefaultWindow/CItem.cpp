#include "pch.h"
#include "CItem.h"
#include "CPlayer.h"
#include "CScrollMgr.h"
#include "CSoundMgr.h"

void CItem::Find_TileIdx_OnMap()
{
	m_iTileIdx = ((int)m_tInfo.fY / TILECY) * TILEX + ((int)m_tInfo.fX / TILECX);
}

void CItem::Find_Player_OnSameTile()
{
	if (m_pTarget != nullptr)
	{
		if ((m_pTarget)->Get_TileIdx() == m_iTileIdx)
			m_bIsPlayerOnTile = true;
		else
			m_bIsPlayerOnTile = false;
	}
}


void CItem::Draw_Price(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	
	HFONT hFont = CreateFont(13, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 
		OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("NecroSans"));
	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	// 글씨 색상 설정
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT);

	// 텍스트 정렬 설정 (중앙 정렬)
	int oldAlign = SetTextAlign(hDC, TA_CENTER);

	// 좌표 설정
	int x = static_cast<int>(m_tInfo.fX);
	int y = (*CTileMgr::Get_Instance()->Get_TileVec())[m_iTileIdx]->Get_Info().fY + 10.f;
	
	// 글씨 출력
	TCHAR szText[32];
	wsprintf(szText, L"%d", m_iPrice);
	TextOut(hDC, x + iScrollX, y + iScrollY, szText, lstrlen(szText));

	// 폰트 해제 및 텍스트 정렬 원래대로 복구
	SetTextAlign(hDC, oldAlign);
	SelectObject(hDC, hOldFont);
	DeleteObject(hFont);
}

void CItem::Play_PurchaseSound()
{

	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT3);
	CSoundMgr::Get_Instance()->PlaySound(L"sfx_pickup_purchase.ogg", SOUND_EFFECT3, 1.f);
}
