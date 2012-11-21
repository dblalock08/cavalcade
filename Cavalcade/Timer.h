// Timer.h
#pragma once

#include <Windows.h>

#define WIN32_LEAN_AND_MEAN

class Timer
{
public:
	Timer();
	~Timer();

	bool Initialize();
	void Update();		// Query the system time and update the time since last query

	float GetTime();		// Returns time since most recent update in ms

private:
	INT64 m_frequency;
	INT64 m_startTime;
	float m_ticksPerMs;
	float m_frameTime;

	SYSTEM_INFO m_sysInfo;
	DWORD m_numProcessors;
	DWORD_PTR m_affinityMask;
	
	HANDLE m_threadHandle;
};