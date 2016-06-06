#include "basic/basic_timer.h"


#ifdef BASIC_WIN
#include <Windows.h>

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

struct timezone
{
    int  tz_minuteswest; /* minutes W of Greenwich */
    int  tz_dsttime;     /* type of dst correction */
};

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    FILETIME ft;
    unsigned __int64 tmpres = 0;
    static int tzflag;

    if (NULL != tv)
    {
        GetSystemTimeAsFileTime(&ft);

        tmpres |= ft.dwHighDateTime;
        tmpres <<= 32;
        tmpres |= ft.dwLowDateTime;

/*converting file time to unix epoch*/
        tmpres -= DELTA_EPOCH_IN_MICROSECS;
        tmpres /= 10;  /*convert into microseconds*/
        tv->tv_sec = (long)(tmpres / 1000000UL);
        tv->tv_usec = (long)(tmpres % 1000000UL);
    }

/*
if (NULL != tz)
{
if (!tzflag)
{
_tzset();
tzflag++;
}
tz->tz_minuteswest = _timezone / 60;
tz->tz_dsttime = _daylight;
}
*/
    return 0;
}

#endif


void BasicTimer::InitTimer()
{
	start_time.tv_sec = 0;
	start_time.tv_usec = 0;
	gettimeofday(&start_time, nullptr);
}

double BasicTimer::GetElapsedTime() const
{
	timeval now;
	gettimeofday(&now, nullptr);
	float seconds = (now.tv_sec - start_time.tv_sec);
	float milliseconds = (float(now.tv_usec - start_time.tv_usec)) / 1000000.0f;
	return seconds + milliseconds;
}

