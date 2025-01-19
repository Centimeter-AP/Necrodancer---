#include "pch.h"
#include "CCoralInst.h"
#include "CBmpMgr.h"
#include "CScrollMgr.h"
#include "CTileMgr.h"
#include "CObjMgr.h"
#include "CBeatMgr.h"
#include "CSoundMgr.h"
#include "Define.h"
#include "CPlayer.h"

void CCoralInst::Play_HitSound()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_MONHIT1);
	CSoundMgr::Get_Instance()->PlaySound(L"en_tentacle_hit.ogg", SOUND_MONHIT1, 0.4f);
}

void CCoralInst::Goto_Player(int _Pos)
{
	m_iMovingPos = _Pos;
	m_bMoveStart = true;
	m_eCurState = SHAKE_ACT;
}

void CCoralInst::Set_HeadPositionIdx()
{
	switch (m_iMovingPos)
	{
	case 1:
		m_iHeadTileIdx = static_cast<CPlayer*>(GET_PLAYER)->Get_HeadTileIdx() - TILEX - 1;
		break;
	case 2:
		m_iHeadTileIdx = static_cast<CPlayer*>(GET_PLAYER)->Get_HeadTileIdx() - TILEX;
		break;
	case 3:
		m_iHeadTileIdx = static_cast<CPlayer*>(GET_PLAYER)->Get_HeadTileIdx() - TILEX + 1;
		break;
	case 4:
		m_iHeadTileIdx = static_cast<CPlayer*>(GET_PLAYER)->Get_HeadTileIdx() - 1;
		break;
	case 6:
		m_iHeadTileIdx = static_cast<CPlayer*>(GET_PLAYER)->Get_HeadTileIdx() + 1;
		break;
	case 7:
		m_iHeadTileIdx = static_cast<CPlayer*>(GET_PLAYER)->Get_HeadTileIdx() + TILEX - 1;
		break;
	case 8:
		m_iHeadTileIdx = static_cast<CPlayer*>(GET_PLAYER)->Get_HeadTileIdx() + TILEX;
		break;
	case 9:
		m_iHeadTileIdx = static_cast<CPlayer*>(GET_PLAYER)->Get_HeadTileIdx() + TILEX + 1;
		break;
	default:
		break;
	}
}

void CCoralInst::Set_TilePos()
{
	CTileMgr::Get_Instance()->Set_TileObject(m_iTileIdx, TOBJ_ENTITY, this);

}

void CCoralInst::Move_Attack()
{
	if (m_eCurState == MOVE_ACT)
	{
		BossInstMove();
	}
}
