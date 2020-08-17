#ifndef PARTPRECISIONMONITOR_HPP
#define PARTPRECISIONMONITOR_HPP 1
#include "IPartPrecisionMonitor.hpp"

class PartPrecisionMonitor : public IPartPrecisionMonitor
{
public:
    PartPrecisionMonitor() : partPrecision(0.0) { }
    virtual ~PartPrecisionMonitor() { }
    virtual float getPartPrecision() { return partPrecision; }
    virtual void setPartPrecision(const float precision)
    {
        partPrecision = precision;
        notify();
    }
private:
    float partPrecision;
};

#endif
