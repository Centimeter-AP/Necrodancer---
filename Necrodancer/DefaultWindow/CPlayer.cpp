#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"
#include "CSceneMgr.h"
#include "CBmpMgr.h"
#include "CSoundMgr.h"
#include "CTileMgr.h"
#include "CNormalShovel.h"
#include "CTitaniumShovel.h"
#include "CBedrock.h"
#include "CDagger.h"
#include "CBeatMgr.h"
#include "CSplash.h"
#include "CWaterTile.h"
#include "CDaggerEffect.h"
#include "CHitRed.h"
#include "CHealing.h"


CPlayer::CPlayer()
	: m_fTime(0.f), m_dwTempTick(0), m_fJumpX(0.f), m_fJumpY(0.f), m_fJumpPower(0.f),
	m_iHeadTileIdx(0), m_bMove(false), m_ePrevDir(DIR_LEFT), m_fShadowY(0.f),
	m_bTemp(false), m_eCurState(IDLE), m_ePreState(IDLE),
	m_pvecTile(nullptr), m_qltskrka(false), m_iMoney(0), m_iWaterTileOffset(0), m_bInWater(false),
	m_bDebugMovable(false), m_bHit(false), m_bHasKey(false), m_iArmorIdx(0)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	//m_tInfo = { WINCX * 0.5f + 24.f, WINCY * 0.5f + 24.f, PLAYERCX, PLAYERCY };
	m_tInfo = { 840, 337, PLAYERCX, PLAYERCY };
	m_pvecTile = CTileMgr::Get_Instance()->Get_TileVec();

	m_iTileIdx = Find_MyTileIdx();
	m_tInfo.fX = (*m_pvecTile)[m_iTileIdx]->Get_Info().fX;
	m_tInfo.fY = (*m_pvecTile)[m_iTileIdx]->Get_Info().fY - 24.f;
	m_fShadowY = m_tInfo.fY - (m_tInfo.fCY * 0.5f) + 4.f;
	
	m_fSpeed = 6.f;
	m_fDistance = 100.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Character/Player_head_left_.bmp", L"Player_Head_L");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Character/Player_head_right.bmp", L"Player_Head_R");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Character/Player_armor_left_.bmp", L"Player_Armor_L");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Character/Player_armor_right.bmp", L"Player_Armor_R");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Character/Player_Shadow.bmp", L"Player_Shadow");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Text/game_beatskipped_1.bmp", L"beatskipped1");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Text/game_beatskipped.bmp", L"beatskipped");

	m_pImgKey = L"Player_Head_L";
	m_eCurState = IDLE;
	m_ePreState = IDLE;
	m_eDir = DIR_UP;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount64();
	m_dwTempTick = GetTickCount64();

	m_eRender = RENDER_GAMEOBJECT;
	m_fJumpPower = 9.5f;
	m_iHeadTileIdx = m_iTileIdx;

	m_iMaxHP = 6;
	m_iHP = 6;

	// 최초 플레이어 init할 때 필수로 들고있어야 하는 아이템들 여기서 생성 후 아이템리스트에 별도로 보관?
	// 좀 비효율적인 것 같긴 한데 고민하느니 일단 만들기..
	// 플레이어말고 오브젝트매니저에서 관리하므로 release에서 관리 필요xxxx
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CNormalShovel>::Create_Item(false));
	m_Itemlist[ITEM_SHOVEL].push_back(CObjMgr::Get_Instance()->Get_LastItem());
	m_Itemlist[ITEM_SHOVEL].back()->Set_Target(this);

	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CDagger>::Create_Item(false));
	m_Itemlist[ITEM_WEAPON].push_back(CObjMgr::Get_Instance()->Get_LastItem());
	m_Itemlist[ITEM_WEAPON].back()->Set_Target(this);
}

int CPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	Key_Input();
	Jumping();
	Get_TileX();
	Get_TileY();
	if (m_bHit)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHitRed>::Create(0));
		m_bHit = false;
	}

	//if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	//{
	//	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CSplash>::Create(m_iTileIdx));
	//	CObjMgr::Get_Instance()->Add_Object(OBJ_STAIR, CAbstractFactory<CWaterTile>::Create(m_iTileIdx));
	//}

	if (m_Itemlist[ITEM_ARMOR].empty() == false)
	{
		m_iArmorIdx = 5;
	}
	// 0이 기본(옷없음), 1이 가죽, 2가 체인, 3이 플레이트
	// 5가 도복


	__super::Update_Rect();
	return OBJ_NOEVENT;
}
void CPlayer::Late_Update()
{
	Offset();
	__super::Move_Frame();
}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC		hMemDChead = CBmpMgr::Get_Instance()->Find_Image(L"Player_Head_R");
	HDC		hMemDCarmor = CBmpMgr::Get_Instance()->Find_Image(L"Player_Armor_R");
	HDC		hMemDCshadow = CBmpMgr::Get_Instance()->Find_Image(L"Player_Shadow");	// 그림자 용 xy 좌표 따로?
	HDC		hMemDCskiptext = CBmpMgr::Get_Instance()->Find_Image(L"beatskipped1");	// 그림자 용 xy 좌표 따로?

	if (m_ePrevDir == DIR_LEFT)
	{
		hMemDChead = CBmpMgr::Get_Instance()->Find_Image(L"Player_Head_L");
		hMemDCarmor = CBmpMgr::Get_Instance()->Find_Image(L"Player_Armor_L");
	}
	if (m_eDir == DIR_UP || m_eDir == DIR_DOWN)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			(int)m_fShadowY + iScrollY, // 그림자 좀만 밑으로 지게
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDCshadow,
			0,
			0,
			PLAYERCX,
			PLAYERCY,
			RGB(255, 0, 255));
	}
	else
	{// 좌우 이동 때 그림자 y축 이동 제거 
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX,
			(int)m_fShadowY + iScrollY, // 그림자 좀만 밑으로 지게
			(int)m_tInfo.fCX,
			(int)m_tInfo.fCY,
			hMemDCshadow,
			0,
			0,
			PLAYERCX,
			PLAYERCY,
			RGB(255, 0, 255));
	}
	if (m_bInWater == true && m_iHeadTileIdx == m_iTileIdx)
	{
		m_iWaterTileOffset = 10;
	}
	else if (m_bInWater == false)
	{
		m_iWaterTileOffset -= 4;
		if (m_iWaterTileOffset < 0)
		{
			m_iWaterTileOffset = 0;
		}
	}

	GdiTransparentBlt(hDC,							//몸통
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY + m_iWaterTileOffset,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY - m_iWaterTileOffset,	// 여기 줄임
		hMemDCarmor,													
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_iArmorIdx,
		PLAYERCX,
		PLAYERCY - m_iWaterTileOffset,			// 여기도 줄임
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,							// 머리
		m_tRect.left + iScrollX,			
		m_tRect.top + iScrollY + m_iWaterTileOffset,
		PLAYERCX,							
		PLAYERCY - m_iWaterTileOffset,
		hMemDChead,							
		PLAYERCX * m_tFrame.iFrameStart,	
		PLAYERCY * m_tFrame.iMotion,		
		PLAYERCX,							
		PLAYERCY - m_iWaterTileOffset,
		RGB(255, 0, 255));					

	//if (m_qltskrka == true)
	//{
	//	TCHAR szText[32];
	//	wsprintf(szText, L"감나빗");
	//	TextOut(hDC, WINCX / 2 - 20, WINCY - 150 - 75, szText, lstrlen(szText));
	//}



	if (CBeatMgr::Get_Instance()->Get_BeatMissed())
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX - 14,
			m_tRect.top + iScrollY - 20,
			77,
			15,
			hMemDCskiptext,
			0,
			0,
			77,
			15,
			RGB(255, 0, 255));
	}

}

void CPlayer::Release()
{
}

bool CPlayer::Can_Move()
{
	float	fHeadX(0.f), fHeadY(0.f);
	fHeadX = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fX;
	fHeadY = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fY;

	if (m_bInWater == true)
		return false;

	return CTileMgr::Get_Instance()->Check_TileObject(m_iHeadTileIdx);

	CObj* pHeadWall = CTileMgr::Get_Instance()->Is_Wall_Exist(fHeadX, fHeadY);
 	CObj* pHeadItem = CObjMgr::Get_Instance()->Is_Item_Exist(m_iHeadTileIdx);
	CObj* pHeadMonster = CObjMgr::Get_Instance()->Is_Monster_Exist(m_iHeadTileIdx);

	if (pHeadWall != nullptr)		// 벽 검사
	{
		CTileMgr::Get_Instance()->Break_Wall(pHeadWall, static_cast<CShovel*>(m_Itemlist[ITEM_SHOVEL].front()));
		return false;
	}
	else if (pHeadMonster != nullptr)
	{
		//Attack
		{
			//pHeadMonster->Set_HP(static_cast<CWeapon*>(m_Itemlist[ITEM_WEAPON].front())->Get_Damage());
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"sfx_general_hit.wav", SOUND_EFFECT, g_fVolume);
			CSoundMgr::Get_Instance()->PlaySound_AttackVoice();
		}
		return false;
	}
	else if (pHeadItem != nullptr) // 아이템 검사
	{
		Get_Item(pHeadItem);
		return true;
	}
	else
		return true;
	return true;
}

void CPlayer::Get_Item(CObj* _pItem)
{
	ITEMLIST	eItemType = dynamic_cast<CItem*>(_pItem)->Get_ItemType();
	switch (eItemType)
	{
	case ITEM_WEAPON:
		break;
	case ITEM_SHOVEL:
		if (!m_Itemlist[ITEM_SHOVEL].empty())
		{
			static_cast<CItem*>(m_Itemlist[ITEM_SHOVEL].back())->Set_OnMap(true);
			m_Itemlist[ITEM_SHOVEL].back()->Set_TileIdx(m_iHeadTileIdx);
			m_Itemlist[ITEM_SHOVEL].back()->Initialize();
			dynamic_cast<CItem*>(_pItem)->Set_OnMap(false);
			_pItem->Set_TileIdx(0);
			//_pItem->Set_Pos(0, 0);
			swap(m_Itemlist[ITEM_SHOVEL].back(), _pItem);

			/*m_Itemlist[ITEM_SHOVEL].pop_back();
			m_Itemlist[ITEM_SHOVEL].push_back(_pItem);*/
			
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"sfx_pickup_weapon.wav", SOUND_EFFECT, g_fVolume);
		}
		else
		{
			m_Itemlist[ITEM_SHOVEL].push_back(_pItem);
			dynamic_cast<CItem*>(_pItem)->Set_OnMap(false);
		}
		break;
	case ITEM_ARMOR:
		break;
	case ITEM_HEAL:
		break;
	case ITEM_GOLD:
		break;
	case ITEM_END:
		break;
	default:
		break;
	}
}


void CPlayer::Jumping()		// 그냥 점프하는 모션만 출력하는거
{
	if (m_bMove) // 실제로 타일을 이동했는가
	{
		float fHeadX = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fX;
		float fHeadY = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fY - 24.f;
		float fCurX = (*m_pvecTile)[m_iTileIdx]->Get_Info().fX;
		float fCurY = (*m_pvecTile)[m_iTileIdx]->Get_Info().fY - 24.f;

		switch (m_eDir)
		{
		case DIR_LEFT:
			m_fJumpPower = 9.5f;

			if (fCurY < m_tInfo.fY)
			{
				m_tInfo.fY = fCurY;
				m_bMove = false;
				m_fTime = 0.f;
				m_iTileIdx = m_iHeadTileIdx;
			}
			else
			{
				m_tInfo.fX -= (m_fSpeed * cosf(45.f * PI / 180) * m_fTime);
				if (fHeadX > m_tInfo.fX)
					m_tInfo.fX = fHeadX;
				m_tInfo.fY -= (m_fJumpPower * sinf(45.f * PI / 180) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
			}
			break;
		case DIR_RIGHT:
			m_fJumpPower = 9.5f;
			if (fCurY < m_tInfo.fY)
			{
				m_tInfo.fY = fCurY;
				m_bMove = false;
				m_fTime = 0.f;
				m_iTileIdx = m_iHeadTileIdx;
			}
			else
			{
				m_tInfo.fX += (m_fSpeed * cosf(45.f * PI / 180) * m_fTime);
				if (fHeadX < m_tInfo.fX)
					m_tInfo.fX = fHeadX;
				m_tInfo.fY -= (m_fJumpPower * sinf(45.f * PI / 180) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
			}
			break;
		case DIR_UP:
			m_fJumpPower = 20.f;

			if (fHeadY > m_tInfo.fY)
			{
				m_tInfo.fY = fHeadY;
				m_fShadowY = fHeadY - 20.f;
				m_bMove = false;
				m_iTileIdx = m_iHeadTileIdx;
				m_fTime = 0.f;
			}
			else
			{
				m_tInfo.fY -= (m_fJumpPower * sinf(45.f * PI / 180) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.1f;
				if ((m_fJumpPower * sinf(45.f * PI / 180) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.2f < 0)
				{
					m_tInfo.fY = fHeadY - 5.f;
					m_iTileIdx = m_iHeadTileIdx;
					m_fTime = 0.f;
				}
			}

			m_fShadowY += -2.f * m_fTime - (9.8f * m_fTime * m_fTime) * 0.45f;

			break;
		case DIR_DOWN:
			m_fJumpPower = 20.f;

			m_tInfo.fY += (m_fJumpPower * sinf(45.f * PI / 180) * m_fTime) - (9.8f * m_fTime * m_fTime);
			if ((m_fJumpPower * sinf(45.f * PI / 180) * m_fTime) - (9.8f * m_fTime * m_fTime) < 0)
			{
				m_tInfo.fY = fHeadY;
				m_bMove = false;
				m_fShadowY = fHeadY - 20.f;
				m_iTileIdx = m_iHeadTileIdx;
				m_fTime = 0.f;
			}
			m_fShadowY -= -6.f * m_fTime - (9.8f * m_fTime * m_fTime);
			if (m_fShadowY > fHeadY - 20.f)
				m_fShadowY = fHeadY - 20.f;

			break;
		default:
			break;
		}
		m_fTime += 0.15f;

	}
	else
	{
		m_fTime = 0.f;
	}

}

void CPlayer::Offset()
{
	int		iOffSetminX = (WINCX >> 1) - 10;
	int		iOffSetmaxX = (WINCX >> 1) + 10;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	//if (m_eDir == DIR_RIGHT || m_eDir == DIR_LEFT)
	{
		if (iOffSetminX > m_tInfo.fX + iScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

		if (iOffSetmaxX < m_tInfo.fX + iScrollX)
			CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
	}

	int		iOffSetminY = (WINCY >> 1) - 10;
	int		iOffSetmaxY = (WINCY >> 1) + 10;
	
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//if (m_eDir == DIR_UP || m_eDir == DIR_DOWN)
	//{
		if (iOffSetminY > m_fShadowY - 20.f + iScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

		if (iOffSetmaxY < m_fShadowY - 20.f + iScrollY)
			CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
	//}



	//int		iOffSetX = WINCX >> 1;

	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	//if (iOffSetX > m_tInfo.fX + iScrollX)
	//	CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	//if (iOffSetX < m_tInfo.fX + iScrollX)
	//	CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
}

CObj* CPlayer::Create_Shield()
{
	return nullptr;
}

void CPlayer::Change_Motion()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CPlayer::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CPlayer::WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CPlayer::ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount64();
			break;

		case CPlayer::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount64();
			break;

		}

		m_ePreState = m_eCurState;
	}

}


void CPlayer::Attack_Effect()
{
	if (static_cast<CWeapon*>(m_Itemlist[ITEM_WEAPON].front())->Get_WeaponType() == CWeapon::DAGGER_TYPE)
	{
		//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CNormalShovel>::Create_Item(false));
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CDaggerEffect>::Create(m_iHeadTileIdx));
	}
}

void CPlayer::Key_Input()
{
	float	fY(0.f);

	// 여기에 박자Mgr->겟박자? 겟..트루?

	//if (m_bBeatCorrect)
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))			// 좌측
		{
			if (BEATMGR->Get_AbleBeatInterval() == true || CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_LOBBY || m_bDebugMovable)		// 키 입력이 가능한 상태인지 (반박자 앞 ~ 반박자 뒤)
			{
				CBeatMgr::Get_Instance()->Set_PlayerActed(true);// 플레이어 행동 여부 true
				CBeatMgr::Get_Instance()->Delete_Bar_Act();		// 가장 앞 노트들 삭제
				CBeatMgr::Get_Instance()->Set_ObjectAbleToMove(true);

				//if (BEATMGR->Get_BeatMissed() == true)
				//{
				//	BEATMGR->Set_BeatMissed(false);
				//}

				m_qltskrka = false;	// 안빗나감
				m_eDir = DIR_LEFT;	// 좌측
				m_ePrevDir = DIR_LEFT;	// 좌측보는중
				m_fShadowY = m_tRect.top + 4.f; // 그림자 top 위치 조정

				if (m_bMove == true) // lobby인지 확인하는 코드 필요? 지금은 작동x
				{
					m_tInfo.fX = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fX;			// 의도한 것 : 이미 움직이고 있던 상태에서 다시 입력시 가려던 타일로 즉시 이동
					m_tInfo.fY = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fY - 24.f;	// 근데 나온 것: 않되
					m_iTileIdx = m_iHeadTileIdx;
				}
				--m_iHeadTileIdx;	// 가고자 하는 타일(좌측)
				if (Can_Move())		// 이동이 가능할 떄 
				{
					m_bMove = true;	// jumping 수행 (변수 이름을 바꾸기?)
					m_tFrame.iFrameStart = 0; // 애니메이션 프레임 제어
				}
				else
					m_iHeadTileIdx = m_iTileIdx;	// 이동이 안되면 가려는 타일을 취소하고 현재 타일로 설정
			}
			else
			{
				CBeatMgr::Get_Instance()->Lose_BeatCombo();
				BEATMGR->Set_InputBeatMissed(true);
				m_qltskrka = true;		// !!감나빗
			}
			if (CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_LOBBY)
				CTileMgr::Get_Instance()->Tile_Shine();

#ifdef  _DEBUG

			cout << "플레이어 위치 : " << m_tInfo.fX << '\t' << m_tInfo.fY << endl;
			cout << "플레이어 위치 타일 : " << m_iTileIdx << endl;

#endif //  _DEBUG
		}

		else if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))
		{
			if (BEATMGR->Get_AbleBeatInterval() == true || CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_LOBBY || m_bDebugMovable)
			{
				CBeatMgr::Get_Instance()->Set_PlayerActed(true);
				CBeatMgr::Get_Instance()->Delete_Bar_Act();
				CBeatMgr::Get_Instance()->Set_ObjectAbleToMove(true);

				m_qltskrka = false;
				m_eDir = DIR_RIGHT;
				m_ePrevDir = DIR_RIGHT;
				m_fShadowY = m_tRect.top + 4.f;

				if (m_bMove == true)
				{
					m_tInfo.fX = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fX;
					m_tInfo.fY = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fY - 24.f;
					m_iTileIdx = m_iHeadTileIdx;
				}
				++m_iHeadTileIdx;
				if (Can_Move())
				{
					m_bMove = true;
					m_tFrame.iFrameStart = 0;
				}
				else
					m_iHeadTileIdx = m_iTileIdx;
			}
			else
			{
				CBeatMgr::Get_Instance()->Lose_BeatCombo();
				BEATMGR->Set_InputBeatMissed(true);
				m_qltskrka = true;
			}
			if (CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_LOBBY)
				CTileMgr::Get_Instance()->Tile_Shine();

#ifdef  _DEBUG

			cout << "플레이어 위치 : " << m_tInfo.fX << '\t' << m_tInfo.fY << endl;
			cout << "플레이어 위치 타일 : " << m_iTileIdx << endl;

#endif //  _DEBUG
		}

		else if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
		{
			if (BEATMGR->Get_AbleBeatInterval() == true || CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_LOBBY || m_bDebugMovable)
			{
				m_qltskrka = false;
				CBeatMgr::Get_Instance()->Set_PlayerActed(true);
				CBeatMgr::Get_Instance()->Delete_Bar_Act();
				CBeatMgr::Get_Instance()->Set_ObjectAbleToMove(true);
				//m_tInfo.fY -= m_fSpeed;
				m_eDir = DIR_UP;
				m_fShadowY = m_tRect.top + 4.f;


				if (m_bMove == true)
				{
					m_tInfo.fX = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fX;
					m_tInfo.fY = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fY - 24.f;
					m_iTileIdx = m_iHeadTileIdx;
				}
				m_iHeadTileIdx -= TILEX;
				if (Can_Move())
				{
					m_bMove = true;
					m_tFrame.iFrameStart = 0;
				}
				else
					m_iHeadTileIdx = m_iTileIdx;
			}
			else
			{
				CBeatMgr::Get_Instance()->Lose_BeatCombo();
				BEATMGR->Set_InputBeatMissed(true);
				m_qltskrka = true;
			}

			if (CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_LOBBY)
				CTileMgr::Get_Instance()->Tile_Shine();

#ifdef  _DEBUG

			cout << "플레이어 위치 : " << m_tInfo.fX << '\t' << m_tInfo.fY << endl;
			cout << "플레이어 위치 타일 : " << m_iTileIdx << endl;

#endif //  _DEBUG
		}

		else if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
		{
			if (BEATMGR->Get_AbleBeatInterval() == true || CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_LOBBY || m_bDebugMovable)
			{
				m_qltskrka = false;
				CBeatMgr::Get_Instance()->Delete_Bar_Act();
				//m_tInfo.fY += m_fSpeed;
				m_eDir = DIR_DOWN;
				m_fShadowY = m_tRect.top + 4.f;
				CBeatMgr::Get_Instance()->Set_PlayerActed(true);
				CBeatMgr::Get_Instance()->Set_ObjectAbleToMove(true);

				if (m_bMove == true)
				{
					m_tInfo.fX = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fX;
					m_tInfo.fY = (*m_pvecTile)[m_iHeadTileIdx]->Get_Info().fY - 24.f;
					m_iTileIdx = m_iHeadTileIdx;
				}
				m_iHeadTileIdx += TILEX;
				if (Can_Move())
				{
					m_bMove = true;
					m_tFrame.iFrameStart = 0;
				}
				else
					m_iHeadTileIdx = m_iTileIdx;
			}
			else
			{
				CBeatMgr::Get_Instance()->Lose_BeatCombo();
				BEATMGR->Set_InputBeatMissed(true);
				m_qltskrka = true;
			}

			if (CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_LOBBY)
				CTileMgr::Get_Instance()->Tile_Shine();
#ifdef  _DEBUG

			cout << "플레이어 위치 : " << m_tInfo.fX << '\t' << m_tInfo.fY << endl;
			cout << "플레이어 위치 타일 : " << m_iTileIdx << endl;

#endif //  _DEBUG
		}
		//m_bBeatCorrect = false;

	}
	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		if (m_Itemlist[ITEM_HEAL].empty() == false)
		{
			if (BEATMGR->Get_AbleBeatInterval() == true || CSceneMgr::Get_Instance()->Get_CurSceneID() == SC_LOBBY || m_bDebugMovable)
			{
				static_cast<CHealing*>(m_Itemlist[ITEM_HEAL].front())->Use_Item();
				m_Itemlist[ITEM_HEAL].pop_front();
				m_qltskrka = false;
				CBeatMgr::Get_Instance()->Delete_Bar_Act();
				CBeatMgr::Get_Instance()->Set_PlayerActed(true);
				CBeatMgr::Get_Instance()->Set_ObjectAbleToMove(true);
			}
		}
		else
		{
			CBeatMgr::Get_Instance()->Lose_BeatCombo();
			BEATMGR->Set_InputBeatMissed(true);
			m_qltskrka = true;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		CBeatMgr::Get_Instance()->Plus_BeatCombo();
 		//m_iMoney += 100; 
		//m_bHit = true;
		m_bDebugMovable = !m_bDebugMovable;
		//m_bHasKey = !m_bHasKey;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('F'))
	{
		m_iMoney += 100;
		m_iHP = m_iMaxHP;
	}

}