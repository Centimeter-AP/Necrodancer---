#include "pch.h"
#include "CStage.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "CBeatMgr.h"
#include "CNormalShovel.h"
#include "CTitaniumShovel.h"
#include "CDagger.h"
#include "CSoundMgr.h"
#include "CHeartbeat.h"
#include "CPlayerHP.h"
#include "CLeftBar.h"
#include "CPlayerShovelUI.h"
#include "CPlayerWeaponUI.h"
#include "CSkeleton.h"
#include "CTauren.h"
#include "CBlueSlime.h"

CStage::CStage() : m_bBeatOne(false), m_iFrameCount(0)
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Tile/Tile.bmp", L"Tile");

	//CLineMgr::Get_Instance()->Initialize();

	CTileMgr::Get_Instance()->Load_Tile();
	CTileMgr::Get_Instance()->Load_Wall();
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CNormalShovel>::Create_Item(true, 404 , 385));
	CObjMgr::Get_Instance()->Get_LastItem()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CDagger>::Create_Item(true, 452 , 385));
	CObjMgr::Get_Instance()->Get_LastItem()->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartbeat>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerHP>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerShovelUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerWeaponUI>::Create());

	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSkeleton>::Create(356, 385));
	//CObjMgr::Get_Instance()->Get_LastMonster()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSkeleton>::Create(256, 385));
	//CObjMgr::Get_Instance()->Get_LastMonster()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSkeleton>::Create(304, 385));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBlueSlime>::Create(304, 289));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTauren>::Create(304, 385));
	//CObjMgr::Get_Instance()->Get_LastMonster()->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	//CSoundMgr::Get_Instance()->PlayBGM(L"BGM_1-1.wav", g_fVolume);
	CBeatMgr::Get_Instance()->Set_MusicStart();
	//CObjMgr::Get_Instance()->

	for (int i = 0; i < 3; ++i)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSkeleton>::Create(float(rand() % WINCX), float(rand() % WINCY), 0.f));
	}
}

int CStage::Update()
{
	//CBeatMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();

	if (CBeatMgr::Get_Instance()->Get_RightTimeBeat())
	{
		if (m_bBeatOne == true)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CLeftBar>::Create_Bar(true));
			CBeatMgr::Get_Instance()->Set_Bar(CObjMgr::Get_Instance()->Get_LastBar());
			CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CLeftBar>::Create_Bar(false));
			CBeatMgr::Get_Instance()->Set_Bar(CObjMgr::Get_Instance()->Get_LastBar());
		}
		m_bBeatOne = false;
	}
	else
	{
		m_bBeatOne = true;
	}
	CObjMgr::Get_Instance()->Update();

	++m_iFrameCount;

	return 0;
}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
	CBeatMgr::Get_Instance()->Late_Update();
}


void CStage::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//BitBlt(hDC, iScrollX, iScrollY, 1920, 1280, hGroundDC, 0, 0, SRCCOPY);
	//CLineMgr::Get_Instance()->Render(hDC);

	CTileMgr::Get_Instance()->Render(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
	CBeatMgr::Get_Instance()->Render(hDC);
}

void CStage::Release()
{
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}	
