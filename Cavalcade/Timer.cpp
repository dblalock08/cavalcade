/****************************************/
/* High performance timer				*/
/*										*/
/* David Blalock 2012					*/
/****************************************/
#include "Timer.h"

Timer::Timer()
{

}

Timer::~Timer()
{

}

bool Timer::Initialize()
{
	// Determine number of processors in the system
	GetSystemInfo(&m_sysInfo);
	m_numProcessors = m_sysInfo.dwNumberOfProcessors;

	m_affinityMask = (1i64 << m_numProcessors);
	
	// Get the thread handle of the calling thread
	m_threadHandle = GetCurrentThread();
	//m_threadHandle = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());	// Alternate method?

	SetThreadAffinityMask(m_threadHandle, m_affinityMask);

	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if (m_frequency == 0)
	{
		// System does not support high performance timer
		return false;
	}

	m_ticksPerMs = (float)(m_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);	// Set initial start time

	// Reset thread affinity
	SetThreadAffinityMask(m_threadHandle, NULL);

	return true;
}

void Timer::Update()
{
	INT64 currentTime;
	float timeDelta;

	// Set thread affinity
	SetThreadAffinityMask(m_threadHandle, m_affinityMask);

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	// Reset thread affinity
	SetThreadAffinityMask(m_threadHandle, NULL);

	timeDelta = (float)(currentTime - m_startTime);
	
	m_frameTime = timeDelta / m_ticksPerMs;

	m_startTime = currentTime;

	return;
}

float Timer::GetTime()
{
	return m_frameTime;
}