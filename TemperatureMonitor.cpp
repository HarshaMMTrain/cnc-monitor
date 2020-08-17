#include "TemperatureMonitor.hpp"

static ITemperatureMonitor * tempMonitor = nullptr;

ITemperatureMonitor* getTemperatureMonitor()
{
    if (nullptr == tempMonitor)
        tempMonitor = new TemperatureMonitor();

    return tempMonitor;
}

