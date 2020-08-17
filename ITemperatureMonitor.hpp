#ifndef ITEMPERATUREMONITOR_HPP
#define ITEMPERATUREMONITOR_HPP 1
#include "ISubject.hpp"

class ITemperatureMonitor : public ISubject
{
public:
    ITemperatureMonitor() { }
    virtual ~ITemperatureMonitor() { }
    virtual float getTemperature() = 0;
    virtual void setTemperature(const float temp) = 0;
};

extern ITemperatureMonitor* getTemperatureMonitor();

#endif
