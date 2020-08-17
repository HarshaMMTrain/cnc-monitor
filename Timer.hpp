#ifndef TIMER_HPP
#define TIMER_HPP 1

#include "ITimer.hpp"
#include "ITimerNotify.hpp"
#include <cstdint>
#include <vector>

class Timer;
class NotifyData;

class Timer : public ITimer
{
public:
    Timer();
    virtual ~Timer();
    uint64_t getTime();
    void setPeriodicAlarm(ITimerNotify* notifyObj, uint32_t period);
    void unsetAlarm(ITimerNotify* notifyObj);
    void dispatchEvents();
    void addTime(const uint32_t &timeIncrement) { timeInSecs += timeIncrement; }
private:
    uint64_t timeInSecs;
    std::vector<NotifyData*> listenerArray;
    int timerFd;

    //void updateTimer();
    NotifyData* getNotifyData(ITimerNotify* notifyObj);
    void eraseNotifyData(ITimerNotify* notifyObj);
};

#endif
