#include "pch.h"
#include "CHitRed.h"

void CHitRed::Initialize()
{
	
	m_eRender = RENDER_HITEFFECT;
}

int CHitRed::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (m_bIsHit)
	{
		++m_iHitFrameCount;
		if (m_iHitFrameCount > 20)
		{
			m_iHitFrameCount = 0;
			m_bIsHit = false;
			m_bDead = true;
		}
	}
    return OBJ_NOEVENT;
}

void CHitRed::Late_Update()
{

}

void CHitRed::Render(HDC hDC)
{
	if (m_bIsHit)
	{
		CDraw::RenderTransparentImage(hDC, L"../content/texture/UI/hit_red.bmp", 0, 75, 800, 450, 50);
	}

}

void CHitRed::Release()
{
}
