#include "pch.h"
#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CLineMgr.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"
#include "CSceneMgr.h"
#include "CTileMgr.h"
#include "CSoundMgr.h"
#include "CBeatMgr.h"
#include "CLetterbox.h"

float	g_fVolume(0.5f);

CMainGame::CMainGame()
	: m_dwTime(GetTickCount64()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	
	srand((unsigned int)time(NULL));

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Title/Buffer_Back.bmp", L"Back");
	CObjMgr::Get_Instance()->Add_Object(OBJ_LETTERBOX, CAbstractFactory<CLetterbox>::Create());
	CSceneMgr::Get_Instance()->Set_Scene(SC_LOGO);
	CSoundMgr::Get_Instance()->Initialize();


//#ifdef _DEBUG
//
//	if (::AllocConsole() == TRUE)
//	{
//		FILE* nfp[3];
//		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
//		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
//		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
//		std::ios::sync_with_stdio();
//	}
//
//#endif // _DEBUG



}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
	CBeatMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
	CKeyMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
	CBeatMgr::Get_Instance()->Late_Update();

}


void CMainGame::Render()
{
#pragma region  FPS Ãâ·Â
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount64();
	}
#pragma endregion
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	CSceneMgr::Get_Instance()->Render(hMemDC);

	BitBlt(m_hDC,
		0, 0, WINCX, WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);
}

void CMainGame::Release()
{
//#ifdef _DEBUG
//
//	FreeConsole();
//
//#endif // 

	CBeatMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::DestroyInstance();
	CSoundMgr::Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);
}
