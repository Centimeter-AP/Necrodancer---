#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"
#include "CLineMgr.h"
#include "CKeyMgr.h"
#include "CScrollMgr.h"
#include "CBmpMgr.h"

CPlayer::CPlayer() 
: m_bJump(false), m_fJumpPower(0.f), m_fTime(0.f), m_dwTempTick(0)

{
	ZeroMemory(&m_tPosin, sizeof(POINT));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo  = { WINCX * 0.5f + 24.f, WINCY * 0.5f + 24.f, PLAYERCX, PLAYERCY };
	m_fSpeed = 48.f;
	m_fDistance = 100.f;

	m_fJumpPower = 20.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Character/Player_head_left_.bmp",  L"Player_Head_L");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Character/Player_head_right.bmp",  L"Player_Head_R");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Character/Player_armor_left_.bmp",  L"Player_Armor_L");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Character/Player_armor_right.bmp",  L"Player_Armor_R");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../content/texture/Character/Player_Shadow.bmp",  L"Player_Shadow");

	m_pImgKey = L"Player_Head_L";
	m_eCurState = IDLE;
	m_ePreState = IDLE;
	m_eDir = DIR_LEFT;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	m_dwTempTick = GetTickCount();

	m_eRender = RENDER_GAMEOBJECT;
}




int CPlayer::Update()
{
	Key_Input();
	Change_Motion();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}
void CPlayer::Late_Update()
{
	Jumping();
	Offset();
	__super::Move_Frame();
}


void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC		hMemDChead = CBmpMgr::Get_Instance()->Find_Image(L"Player_Head_R");
	HDC		hMemDCarmor = CBmpMgr::Get_Instance()->Find_Image(L"Player_Armor_R");
	HDC		hMemDCshadow = CBmpMgr::Get_Instance()->Find_Image(L"Player_Shadow");				// 그림자 용 xy 좌표 따로?

	if (m_eDir == DIR_LEFT)
	{
		hMemDChead = CBmpMgr::Get_Instance()->Find_Image(L"Player_Head_L");
		hMemDCarmor = CBmpMgr::Get_Instance()->Find_Image(L"Player_Armor_L");
	}

	GdiTransparentBlt(hDC,		
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,		
		(int)m_tInfo.fCY,
		hMemDCshadow,			
		0,						
		0,
		PLAYERCX,			
		PLAYERCY,			
		RGB(255, 0, 255));		

	GdiTransparentBlt(hDC,			
		m_tRect.left + iScrollX,	
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,			
		(int)m_tInfo.fCY,
		hMemDCarmor,				
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,	
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		PLAYERCX,			
		PLAYERCY,			
		RGB(255, 0, 255));	


	GdiTransparentBlt(hDC,					// 복사 받을 DC
		m_tRect.left + iScrollX,			// 복사 받을 위치 좌표 X, Y	
		m_tRect.top + iScrollY,
		PLAYERCX,							// 복사 받을 이미지의 가로, 세로
		PLAYERCY,
		hMemDChead,							// 복사할 이미지 DC	
		PLAYERCX * m_tFrame.iFrameStart,	// 비트맵 출력 시작 좌표(Left, top)
		PLAYERCY * m_tFrame.iMotion,
		PLAYERCX,							// 복사할 이미지의 가로, 세로
		PLAYERCY,
		RGB(255, 0, 255));					// 제거할 색상
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	float	fY(0.f);

	// 여기에 박자Mgr->겟박자? 겟..트루?

	if (m_dwTempTick + 500 < GetTickCount())
	{

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
			m_eDir = DIR_LEFT;
			m_tFrame.iFrameStart = 0;
			m_eCurState = WALK;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
			m_eDir = DIR_RIGHT;
			m_tFrame.iFrameStart = 0;
			m_eCurState = WALK;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fY -= m_fSpeed;
			m_tFrame.iFrameStart = 0;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_tInfo.fY += m_fSpeed;
			m_tFrame.iFrameStart = 0;
		}
		m_dwTempTick = GetTickCount();
	}
}

void CPlayer::Jumping()
{
	float	fY(0.f);

	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		m_tInfo.fY -= (m_fJumpPower * sinf(45.f) * m_fTime) - (9.8f * m_fTime * m_fTime) * 0.5f;
		m_fTime += 0.2f;

		if (bLineCol && (fY < m_tInfo.fY))
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	else if (bLineCol)
	{
		m_tInfo.fY = fY;
	}
}

void CPlayer::Offset()
{

	int		iOffSetminX = 100;
	int		iOffSetmaxX = 700;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (iOffSetminX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetmaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	int		iOffSetminY = 100;
	int		iOffSetmaxY = 500;

	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffSetminY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffSetmaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

CObj* CPlayer::Create_Shield()
{
	CObj* pShield = CAbstractFactory<CShield>::Create();
	
	pShield->Set_Target(this);

	return pShield;
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
			m_tFrame.dwTime = GetTickCount();
			break;

		case CPlayer::WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case CPlayer::ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case CPlayer::HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case CPlayer::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;	
		}

		m_ePreState = m_eCurState;
	}

}


