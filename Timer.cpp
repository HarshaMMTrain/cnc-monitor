#include "Timer.hpp"
#include <algorithm>
#include <sys/timerfd.h>
#include <time.h>
#include <unistd.h>
#include <iostream>

static Timer SysTimer;

class NotifyData
{
public:
    NotifyData(ITimerNotify* notify, const uint32_t &timeDiff,
        const uint64_t absoluteTime) :
        listener(notify),
        period(timeDiff),
        startTime(absoluteTime),
        lastNotifyTime(0)
    {
    }
    virtual ~NotifyData()
    {
    }
    ITimerNotify *listener;
    uint32_t period;
    uint64_t startTime;
    uint64_t lastNotifyTime;
};

ITimer* getSystemTimer()
{
    return &SysTimer;
}

Timer::Timer():
    timeInSecs(0),
    listenerArray(),
    timerFd(-1)
{
    struct itimerspec timerSettings;
    
    timerFd = timerfd_create(CLOCK_MONOTONIC,
                             TFD_CLOEXEC);
    
    timerSettings.it_value.tv_nsec = 1000;
    timerSettings.it_value.tv_sec = 0;
    timerSettings.it_interval.tv_nsec = 0;
    timerSettings.it_interval.tv_sec = 1;
    timerfd_settime(timerFd, 0, &timerSettings, NULL);
}

Timer::~Timer()
{
    close(timerFd);
}

uint64_t
Timer::getTime()
{
    return timeInSecs;    
}

void
Timer::setPeriodicAlarm(ITimerNotify* notifyObj, uint32_t period)
{
    NotifyData* clientData;
    clientData = getNotifyData(notifyObj);
    if (nullptr == clientData)
    {
        clientData = new NotifyData(notifyObj, period, timeInSecs);
        listenerArray.push_back(clientData);
    }
}

void
Timer::unsetAlarm(ITimerNotify* notifyObj)
{
    eraseNotifyData(notifyObj);
}

/*
void
Timer::updateTimer()
{
    uint64_t elapsedSeconds = 0;
    read(timerFd, &elapsedSeconds, sizeof(uint64_t));
    timeInSecs += elapsedSeconds;
}
*/
void
Timer::dispatchEvents()
{
//    updateTimer();
    for (auto& nData : listenerArray)
    {
        uint32_t elapsedTimeSinceStart;
        elapsedTimeSinceStart = timeInSecs - nData->startTime;
        if ((elapsedTimeSinceStart / nData->period) >
            (nData->lastNotifyTime / nData->period))
        {
            nData->lastNotifyTime = elapsedTimeSinceStart;
            nData->listener->notification();
        }
    }
}

NotifyData*
Timer::getNotifyData(ITimerNotify* notifyObj)
{
    NotifyData* ret = nullptr;
    for (auto& nData: listenerArray)
    {
        if (nData->listener == notifyObj)
        {
            ret = nData;
            break;
        }
    }
    return ret;
}

void
Timer::eraseNotifyData(ITimerNotify* notifyObj)
{
    std::vector<NotifyData*>::iterator iter = listenerArray.begin();

    for (; iter != listenerArray.end(); ++iter)
    {
        if ((*iter)->listener == notifyObj)
        {
            listenerArray.erase(iter);
            break;
        }
    }
}

