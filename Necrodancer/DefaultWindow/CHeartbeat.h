#pragma once
#include "CObj.h"
class CHeartbeat : public CObj
{
public:
	CHeartbeat(): m_iBeat(0), m_llTimeChecker(0), m_ullBPM(0), m_ullTimeTick(0) {}
	~CHeartbeat() {}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	int m_iBeat;
	ULONGLONG m_ullTimeTick;
	ULONGLONG m_ullBPM;

	chrono::system_clock::time_point m_tBeatStart;
	chrono::system_clock::time_point m_tTimerRightTime;
	chrono::duration<double> m_llTimeChecker;


};

