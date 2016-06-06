#ifndef __BASIC_TIMER_H__
#define __BASIC_TIMER_H__

#ifdef BASIC_ANDROID
#include <sys/time.h>
#endif

#ifdef BASIC_TIZEN
#include <sys/time.h>
#endif

#ifdef BASIC_WIN
#include <Windows.h>
#endif

class BasicTimer
{
	timeval start_time;

public:
	void InitTimer();

	double GetElapsedTime() const;
};


#endif //__BASIC_TIMER_H__


