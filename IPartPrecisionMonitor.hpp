#ifndef IPARTPRECISIONMONITOR_HPP
#define IPARTPRECISIONMONITOR_HPP 1
#include "ISubject.hpp"

class IPartPrecisionMonitor : public ISubject
{
public:
    IPartPrecisionMonitor() { }
    virtual ~IPartPrecisionMonitor() { }
    virtual float getPartPrecision() = 0;
    virtual void setPartPrecision(const float precision) = 0;
};

extern IPartPrecisionMonitor* getPartPrecisionMonitor();

#endif
