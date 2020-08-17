#include "PartPrecisionMonitor.hpp"

static IPartPrecisionMonitor * partPrecisionMonitor = nullptr;

IPartPrecisionMonitor* getPartPrecisionMonitor()
{
    if (nullptr == partPrecisionMonitor)
        partPrecisionMonitor = new PartPrecisionMonitor();

    return partPrecisionMonitor;
}
