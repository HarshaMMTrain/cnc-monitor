#ifndef OPTIMEMONITOR_HPP
#define OPTIMEMONITOR_HPP 1
#include "IOptimeMonitor.hpp"
#include "ITimerNotify.hpp"
#include "ITimer.hpp"

class OptimeMonitor;

class OptimeMonitor : public IOptimeMonitor
{
    class TimerAlarm : public ITimerNotify
    {
    public:
        explicit TimerAlarm(OptimeMonitor *optimeMonitor) : notifyObject(optimeMonitor) { }
        virtual ~TimerAlarm() { }
        virtual void notification()
        {
            notifyObject->notify();
            notifyObject->addOptime();
        }
    private:
        OptimeMonitor* notifyObject;
    };
public:
    OptimeMonitor():
        optime(0),
        alarm(this)
    {
        sysTimer = getSystemTimer();
        //set repetitive alarm for 15mins
        sysTimer->setPeriodicAlarm(&alarm, 900);
        startTime = sysTimer->getTime();
    }
    virtual ~OptimeMonitor()
    {
        sysTimer->unsetAlarm(&alarm);
    }
    virtual uint32_t getOptime() { return optime; }
private:
    uint64_t startTime;
    uint32_t optime;
    TimerAlarm alarm;
    ITimer *sysTimer;

    void addOptime() { optime = (uint32_t)(sysTimer->getTime() - startTime); }
};

#endif
