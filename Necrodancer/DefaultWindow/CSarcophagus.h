#pragma once
#include "CObj.h"
class CSarcophagus :
    public CObj
{
public:
	CSarcophagus() : m_bIsOpen(false) {}
	virtual ~CSarcophagus() {}
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
	void Set_IsOpen(bool _bIsOpen) { m_bIsOpen = _bIsOpen; }    
	bool Get_IsOpen() { return m_bIsOpen; }
private:
    bool    m_bIsOpen;
};

