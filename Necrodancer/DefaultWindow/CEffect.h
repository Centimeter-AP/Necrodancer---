#pragma once
#include "CObj.h"
class CEffect : public CObj
{
public:
	CEffect() : m_iImgfX(0), m_iImgfY(0), m_iImgfCX(0), m_iImgfCY(0){}
	virtual ~CEffect() {}
public:
	void Initialize() PURE;
	int Update() PURE;
	void Late_Update() PURE;
	void Render(HDC hDC) PURE;
	void Release() PURE;
protected:
	int m_iImgfX;
	int m_iImgfY;
	int m_iImgfCX;
	int m_iImgfCY;
};

