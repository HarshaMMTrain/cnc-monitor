#ifndef TEMPERATUREMONITOR_HPP
#define TEMPERATUREMONITOR_HPP 1
#include "ITemperatureMonitor.hpp"
#include "ITimerNotify.hpp"
#include "ITimer.hpp"

class TemperatureMonitor;

class TemperatureMonitor : public ITemperatureMonitor
{
    class TimerAlarm : public ITimerNotify
    {
    public:
        explicit TimerAlarm(TemperatureMonitor *tempMonitor) : notifyObject(tempMonitor) { }
        virtual ~TimerAlarm() { }
        virtual void notification() { notifyObject->notify(); }
    private:
        TemperatureMonitor* notifyObject;
    };
public:
    TemperatureMonitor():
        temperature(0.0),
        alarm(this)
    {
        sysTimer = getSystemTimer();
        //set repetitive alarm for 30mins
        sysTimer->setPeriodicAlarm(&alarm, 1800);
    }
    virtual ~TemperatureMonitor()
    {
        sysTimer->unsetAlarm(&alarm);
    }
    virtual float getTemperature() { return temperature; }
    virtual void setTemperature(const float temp) { temperature = temp; }
private:
    float temperature;
    TimerAlarm alarm;
    ITimer *sysTimer;
};

#endif
