#pragma once

#define WINCX		800
#define WINCY		600

#define	PURE		= 0
#define PI			3.141592f

#define OBJ_NOEVENT			0
#define OBJ_DEAD			1	
#define OBJ_NEXTSCENE		2

#define VK_MAX				0xff

#define TILEX				51
#define TILEY				50
#define	TILECX				48
#define	TILECY				48

#define PLAYERCX			TILECX
#define PLAYERCY			TILECY

#define G_FORCE                9.80665f
#define SQUARE(X)            (X)*(X)
#define RADIAN(Degree)        (Degree)*PI/180.f
#define DEGREE(Radian)        (Radian)*180.f/PI

#define KEY_DOWN(X)        CKeyMgr::Get_Instance()->Key_Down(X)
#define KEY_PRESSING(X)        CKeyMgr::Get_Instance()->Key_Pressing(X)
#define KEY_UP(X)        CKeyMgr::Get_Instance()->Key_Up(X)

#define GET_IMAGE(X) CBmpMgr::Get_Instance()->Find_Image(X)
#define INSERT_BMP CBmpMgr::Get_Instance()->Insert_Bmp

#define SCROLLX CScrollMgr::Get_Instance()->Get_ScrollX()
#define SCROLLY CScrollMgr::Get_Instance()->Get_ScrollY()

#define ADD_OBJ CObjMgr::Get_Instance()->Add_Object
#define CREATE_OBJ(X) CAbstractFactory< X >::Create_Obj
#define CREATE_IDX(X) CAbstractFactory< X >::Create
#define GET_PLAYER CObjMgr::Get_Instance()->Get_Player()

#define BEATMGR CBeatMgr::Get_Instance()

#define	STAGE1BPM		115
#define STAGE1BPMSEC	(int)((60.f / (float)STAGE1BPM) * 1000000.f)
#define BOSSBPM			126
#define BOSSBPMSEC		(int)((60.f / (float)BOSSBPM) * 1000000.f)

extern HWND		g_hWnd;
extern float	g_fVolume;

enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_END };

enum OBJID { OBJ_PLAYER, OBJ_LETTERBOX, OBJ_ITEM, OBJ_BEAT, OBJ_STAIR, OBJ_MONSTER, OBJ_GOLD, OBJ_BUTTON, OBJ_EFFECT, OBJ_UI, OBJ_END };

enum RENDERID { RENDER_BACKGROUND, RENDER_MAPITEM, RENDER_GAMEOBJECT, RENDER_BEAT, RENDER_EFFECT, RENDER_OBJUI, RENDER_UI, RENDER_HITEFFECT, RENDER_LETTERBOX, RENDER_END };

enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_LOBBY, SC_STAGEONE, SC_BOSS, SC_STAGE, SC_END };
enum STAGEID { STAGE_LOBBY, STAGE_ONE, STAGE_BOSS, STAGE_END };

enum CHANNELID { SOUND_MONHIT1, SOUND_MONHIT2, SOUND_MONDEATH1, SOUND_MONDEATH2, SOUND_EFFECT, SOUND_EFFECT2, SOUND_EFFECT3, SOUND_EFFECT4, SOUND_EFFECT5, SOUND_VOCAL, SOUND_BGM, SOUND_BOSS0, SOUND_BOSS1, SOUND_BOSS2, SOUND_BOSS3, SOUND_BOSS4, SOUND_BOSSEFFECT1, SOUND_BOSSEFFECT2, SOUND_BOSSEFFECT3, SOUND_BOSSEFFECT4, SOUND_MERCHANT, SOUND_END };

enum TILEOPTIONID { OPT_TILE, OPT_WALL, OPT_ITEM, OPT_ENTITY, OPT_TRAP, OPT_END };

enum WALLTYPE { DIRT_WALL, STONE_WALL, SHOP_WALL, BEDROCK, DOOR_WALL, VDOOR_WALL, WALL_END };

enum WALLPOWER {NO_POWER = 0, POWER_ONE = 1, POWER_TWO, POWER_THREE, POWER_BOMB = 10, POWER_NOEXCEPTION = 999, POWER_END };

enum ITEMLIST {ITEM_WEAPON, ITEM_SHOVEL, ITEM_ARMOR, ITEM_HEAL, ITEM_GOLD, ITEM_END};

enum TILEOBJECT {TOBJ_ENTITY, TOBJ_ITEM, TOBJ_WALL, TOBJ_TRAP, TOBJ_STAIR, TOBJ_END};

//enum BOSSINST {DRUM_L, DRUM_R, BRASS_L, BRASS_R, VIOLIN_L, VIOLIN_R, PIANO_L, PIANO_R, INST_END};

//enum DrawID {   };

#include "CDraw.h"

typedef struct tagInfo
{
	float		fX, fY;
	float		fCX, fCY;	// 가로, 세로 길이

}INFO;

typedef struct tagLinePoint
{
	float		fX, fY;

	tagLinePoint()	{ZeroMemory(this, sizeof(tagLinePoint));}
		tagLinePoint(float _fX, float _fY)
		: fX(_fX), fY(_fY)
	{	}

}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT	tLPoint;
	LINEPOINT	tRPoint;

	tagLine() { 	ZeroMemory(this, sizeof(tagLine));	}
	tagLine(LINEPOINT& _tLPoint, LINEPOINT& _tRPoint)
		: tLPoint(_tLPoint), tRPoint(_tRPoint) {	}

}LINE;

typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;
	ULONGLONG	dwSpeed;
	ULONGLONG	dwTime;

}FRAME;


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

struct tagFinder
{
public:
	tagFinder(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool	operator()(T& rObj)
	{
		return !lstrcmp(m_pString, rObj.first);
	}

private:
	const TCHAR* m_pString;
};

struct DeleteMap
{
public:
	template<typename T>
	void	operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};