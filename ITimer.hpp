#ifndef ITIMER_HPP
#define ITIMER_HPP 1

#include "ITimerNotify.hpp"
#include <cstdint>

class ITimer
{
public:
    ITimer() { }
    virtual ~ITimer() { }
    virtual uint64_t getTime() = 0;
    virtual void setPeriodicAlarm(ITimerNotify* notifyObj, uint32_t period) = 0;
    virtual void unsetAlarm(ITimerNotify* notifyObj) = 0;
    virtual void dispatchEvents() = 0;
    virtual void addTime(const uint32_t &timeIncrement) = 0;
};

extern ITimer* getSystemTimer();

#endif


