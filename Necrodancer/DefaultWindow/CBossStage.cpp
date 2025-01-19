#include "pch.h"
#include "CBossStage.h"
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
#include "CStair.h"
#include "CCoralRiffBoss.h"
#include "CCoralViolin.h"
#include "CCoralPiano.h"
#include "CCoralDrum.h"
#include "CCoralBrass.h"
#include "CKeyMgr.h"
#include "CWaterTile.h"
#include "CBossCutscene.h"
#include "CGoldenKey.h"
#include "CPlayerMoney.h"
#include "CPlayerHealingUI.h"
#include "CPlayerArmorUI.h"

CBossStage::CBossStage() : m_bPlayerEntered(false), m_bPlayerCleared(false)
, m_bPlayerEnteredCheck(false), m_bPlayerClearedCheck(false)
, m_bCutscene(false), m_bCutsceneCheck(false)
{
}

CBossStage::~CBossStage()
{
	Release();
}

void CBossStage::Initialize()
{
	BEATMGR->Empty_Bar();
	for (int i = OBJ_BEAT; i < OBJ_END; ++i)
	{
		CObjMgr::Get_Instance()->Delete_ID((OBJID)i);
	}
	CObjMgr::Get_Instance()->Delete_Map_Item();
	
	CTileMgr::Get_Instance()->Load_Tile(STAGE_BOSS);
	CTileMgr::Get_Instance()->Load_Wall(STAGE_BOSS);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	GET_PLAYER->Set_Pos(408, 1056);
	static_cast<CPlayer*>(GET_PLAYER)->Set_PositionCorrect();
	static_cast<CPlayer*>(GET_PLAYER)->Set_FirstTileIdx();
	BEATMGR->Set_BPMBOSS();
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartbeat>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerHP>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerHealingUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerArmorUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerShovelUI>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerMoney>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CPlayerWeaponUI>::Create());
	//CObjMgr::Get_Instance()->Add_Object(OBJ_STAIR, CAbstractFactory<CStair>::Create(1320, 934));
	//static_cast<CStair*>(CObjMgr::Get_Instance()->Get_LastStair())->Set_NextScene(SC_BOSS);

	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTauren>::Create_Monster(500, 384));

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CCoralRiffBoss>::Create_Monster(408, 384));
	CCoralRiffBoss* Boss = static_cast<CCoralRiffBoss*>(CObjMgr::Get_Instance()->Get_LastMonster());

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CCoralDrum>::Create_Monster(168, 432));
	Boss->Set_Inst(CObjMgr::Get_Instance()->Get_LastMonster());
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CCoralDrum>::Create_Monster(648, 432));
	Boss->Set_Inst(CObjMgr::Get_Instance()->Get_LastMonster());

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CCoralBrass>::Create_Monster(216, 408));
	Boss->Set_Inst(CObjMgr::Get_Instance()->Get_LastMonster());
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CCoralBrass>::Create_Monster(600, 408));
	Boss->Set_Inst(CObjMgr::Get_Instance()->Get_LastMonster());

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CCoralViolin>::Create_Monster(240, 408));
	Boss->Set_Inst(CObjMgr::Get_Instance()->Get_LastMonster());
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CCoralViolin>::Create_Monster(528, 408));
	Boss->Set_Inst(CObjMgr::Get_Instance()->Get_LastMonster());

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CCoralPiano>::Create_Monster(312, 384));
	Boss->Set_Inst(CObjMgr::Get_Instance()->Get_LastMonster());
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CCoralPiano>::Create_Monster(488, 384));
	Boss->Set_Inst(CObjMgr::Get_Instance()->Get_LastMonster());


	//auto pTile = CTileMgr::Get_Instance()->Get_TileVec();
	//pTile->push_back(CAbstractFactory<CWaterTile>::Create(569));
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 411 + i * 51; j < (411 + i * 51) + 11; ++j)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_STAIR, CAbstractFactory<CWaterTile>::Create(j));
		}
	}
	
	//CObjMgr::Get_Instance()->Add_Object(OBJ_STAIR, CAbstractFactory<CWaterTile>::Create(569));

	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CCoralBrass>::Create_Monster(408, 500));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSkeleton>::Create_Monster(216, 384));
	CScrollMgr::Get_Instance()->Set_Scroll(0, -523);

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"boss_4_inst0Bass.ogg", 0.2f, SOUND_BOSS0);
	CSoundMgr::Get_Instance()->PlayBGM(L"boss_4_inst1Drum.ogg", 0.2f, SOUND_BOSS1);
	CSoundMgr::Get_Instance()->PlayBGM(L"boss_4_inst2Brass.ogg", 0.2f, SOUND_BOSS2);
	CSoundMgr::Get_Instance()->PlayBGM(L"boss_4_inst3Violin.ogg", 0.2f, SOUND_BOSS3);
	CSoundMgr::Get_Instance()->PlayBGM(L"boss_4_inst4Piano.ogg", 0.2f, SOUND_BOSS4);
	CSoundMgr::Get_Instance()->StopSound(SOUND_VOCAL);
	CSoundMgr::Get_Instance()->PlaySound(L"vo_announcer_coralriff.ogg", SOUND_VOCAL, 0.2f);
	CBeatMgr::Get_Instance()->Set_MusicStart();
	ADD_OBJ(OBJ_UI, CREATE_IDX(CBossCutscene)(0));
}

int CBossStage::Update()
{
	//CBeatMgr::Get_Instance()->Update();
	//if (CTileMgr::Get_Instance()->Get_TileVec()->)

	CTileMgr::Get_Instance()->Update();

	if (CBeatMgr::Get_Instance()->Get_RightTimeBeat())
	{
		if (m_bBeatOne == true)
		{
			CTileMgr::Get_Instance()->Tile_Shine();

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
	if (CObjMgr::Get_Instance()->Get_MonsterList().empty() == true)
	{
		m_bPlayerCleared = true;
	}
	CObjMgr::Get_Instance()->Update();

	++m_iFrameCount;

	//if (CKeyMgr::Get_Instance()->Key_Down('1'))
	//{

	//	CTileMgr::Get_Instance()->Load_Tile1();
	//	CTileMgr::Get_Instance()->Load_Wall1();
	//}
	//if (CKeyMgr::Get_Instance()->Key_Down('2'))
	//{
	//	CTileMgr::Get_Instance()->Load_Tile2();
	//	CTileMgr::Get_Instance()->Load_Wall2();
	//}
	if (m_bPlayerEntered == false)
	{
		if (GET_PLAYER->Get_TileIdx() >= 772 && GET_PLAYER->Get_TileIdx() <= 774)
			m_bPlayerEntered = true;
	}

	if (m_bPlayerEnteredCheck == false && m_bPlayerEntered == true)
	{
		// Äç ¼Ò¸®
		CSoundMgr::Get_Instance()->PlaySound(L"boss_zone1_walls.ogg", SOUND_EFFECT2, 0.13f);
		// ¸÷ Å¸ÀÏ ÀÎµ¦½º ´Ù½Ã È®ÀÎ
		
		CTileMgr::Get_Instance()->Load_Tile1();
		CTileMgr::Get_Instance()->Load_Wall1();
		static_cast<CCoralRiffBoss*>(CObjMgr::Get_Instance()->Get_FirstMonster())->Set_InstTilePos();
		static_cast<CCoralRiffBoss*>(CObjMgr::Get_Instance()->Get_FirstMonster())->Set_Phase(1);
		m_bPlayerEnteredCheck = true;
	}
	if (m_bPlayerClearedCheck == false && m_bPlayerCleared == true)
	{
		CTileMgr::Get_Instance()->Load_Tile2();
		CTileMgr::Get_Instance()->Load_Wall2();
		// 408 240 / 263

		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CGoldenKey>::Create());
		CObjMgr::Get_Instance()->Add_Object(OBJ_STAIR, CAbstractFactory<CStair>::Create(408, 264));
		static_cast<CStair*>(CObjMgr::Get_Instance()->Get_LastStair())->Set_NextScene(SC_LOBBY);
		m_bPlayerClearedCheck = true;
	}

	return 0;
}

void CBossStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
	CBeatMgr::Get_Instance()->Late_Update();
}

void CBossStage::Render(HDC hDC)
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

void CBossStage::Release()
{
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}
