#include "pch.h"
#include "CShovel.h"
#include "CPlayer.h"

void CShovel::Get_RenderPos()
{
	if (!m_pTarget)
		return;
	switch (m_pTarget->Get_Direction())
	{
	case DIR_LEFT:
		m_tInfo.fX = m_pTarget->Get_Info().fX - 48.f;
		m_tInfo.fY = m_pTarget->Get_Info().fY + 18.f;
		break;
	case DIR_RIGHT:
		m_tInfo.fX = m_pTarget->Get_Info().fX + 48.f;
		m_tInfo.fY = m_pTarget->Get_Info().fY + 18.f;
		break;
	case DIR_UP:
		m_tInfo.fX = m_pTarget->Get_Info().fX;
		m_tInfo.fY = m_pTarget->Get_Info().fY - 30.f;
		break;
	case DIR_DOWN:
		m_tInfo.fX = m_pTarget->Get_Info().fX;
		m_tInfo.fY = m_pTarget->Get_Info().fY + 66.f;
		break;
	}
}
