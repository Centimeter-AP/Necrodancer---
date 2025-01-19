#include "pch.h"
#include "CLetterbox.h"
#include "CBmpMgr.h"

void CLetterbox::Initialize()
{
	m_tInfo = {0, 0, WINCX , 75};
	m_pImgKey = L"Letterbox";



	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/UI/Letterbox.bmp", L"Letterbox");
	m_eRender = RENDER_LETTERBOX;
}

int CLetterbox::Update()
{
	return OBJ_NOEVENT;
}

void CLetterbox::Late_Update()
{
}

void CLetterbox::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pImgKey);

	BitBlt(hDC,
		0,
		0,
		WINCX,
		75,
		hMemDC,
		0,
		0,
		SRCCOPY);
	BitBlt(hDC,
		0,
		WINCY - 75,
		WINCX,
		75,
		hMemDC,
		0,
		0,
		SRCCOPY);
}

void CLetterbox::Release()
{
}
