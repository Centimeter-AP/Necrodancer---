#include "pch.h"
#include "CLobby.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CBmpMgr.h"
#include "CAbstractFactory.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "CBeatMgr.h"
#include "CSoundMgr.h"
#include "CPlayerHP.h"
#include "CPlayerShovelUI.h"
#include "CPlayerWeaponUI.h"
#include "CStair.h"
#include "CDummy.h"
#include "CSarcophagus.h"
#include "CGoldenKey.h"
#include "CPlayerMoney.h"


CLobby::CLobby()
{
}

CLobby::~CLobby()
{
	Release();
}

void CLobby::Initialize()
{
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Tile/Tile.bmp", L"Tile");

	//CLineMgr::Get_Instance()->Initialize();

	BEATMGR->Empty_Bar();
	for (int i = OBJ_BEAT; i < OBJ_END; ++i)
	{
		CObjMgr::Get_Instance()->Delete_ID((OBJID)i);
	}
	CObjMgr::Get_Instance()->Delete_Map_Item();
	BEATMGR->Lose_BeatCombo();


	CTileMgr::Get_Instance()->Load_Tile(STAGE_LOBBY);
	CTileMgr::Get_Instance()->Load_Wall(STAGE_LOBBY);
	if (CObjMgr::Get_Instance()->Check_IsPlayerEmpty() == false)
	{
		GET_PLAYER->Set_Pos(840, 337);
		static_cast<CPlayer*>(GET_PLAYER)->Set_PositionCorrect();
		static_cast<CPlayer*>(GET_PLAYER)->Set_FirstTileIdx();
		static_cast<CPlayer*>(GET_PLAYER)->Set_FullHP();
	}
	else
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(840,337));

	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerHP>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerShovelUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerWeaponUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_STAIR, CAbstractFactory<CStair>::Create(792, 456));
	static_cast<CStair*>(CObjMgr::Get_Instance()->Get_LastStair())->Set_NextScene(SC_STAGEONE);
	CObjMgr::Get_Instance()->Add_Object(OBJ_STAIR, CAbstractFactory<CStair>::Create(888, 456));
	static_cast<CStair*>(CObjMgr::Get_Instance()->Get_LastStair())->Set_NextScene(SC_BOSS);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSarcophagus>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerMoney>::Create());

	CScrollMgr::Get_Instance()->Set_ScrollX(-430);
	CScrollMgr::Get_Instance()->Set_ScrollY(330);
	static_cast<CPlayer*>(GET_PLAYER)->Set_FirstTileIdx();
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"lobby.ogg", 0.2f);

	// 피타격 테스트용 더미
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CDummy>::Create_Monster(840 - 48, 337 - 48));

}

int CLobby::Update()
{
	//CBeatMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

	//++m_iFrameCount;

	return 0;
}

void CLobby::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
}


void CLobby::Render(HDC hDC)
{
	HDC		hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	CTileMgr::Get_Instance()->Render(hDC);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CLobby::Release()
{
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}
