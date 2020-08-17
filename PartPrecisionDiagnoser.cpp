#include "PartPrecisionDiagnoser.hpp"
#include "DiagnoserRegister.hpp"
#include "IPartPrecisionMonitor.hpp"

REGISTER_TO_DIAGFACTORY(PartPrecisionDiagnoser, "partprecision")

PartPrecisionDiagnoser::PartPrecisionDiagnoser() :
    diagName("partprecision"),
    partPrecision(0.0),
    sendNotify(false),
    partPrecisionNotifier(this)
{
    partPrecisionSource = getPartPrecisionMonitor();
    partPrecisionSource->addObserver(&partPrecisionNotifier);
}

PartPrecisionDiagnoser::~PartPrecisionDiagnoser()
{
    partPrecisionSource->removeObserver(&partPrecisionNotifier);
}

void
PartPrecisionDiagnoser::readPartPrecision()
{
    partPrecision = partPrecisionSource->getPartPrecision();
    if (partPrecision > 0.05)
    {
        sendNotify = true;
    }
}

bool
PartPrecisionDiagnoser::getDiagnosis(std::string &diagnosis)
{
    bool ret = false;
    if (partPrecision > 0.05)
    {
        diagnosis.assign("partprecision: beyond the acceptable higher limit(0.05mm)");
    }
    else
    {
        ret = true;
        diagnosis.assign("partprecision: OK ");
    }
    return ret;
}

void
PartPrecisionDiagnoser::dispatchEvents()
{
    if (sendNotify)
    {
        sendNotify = false;
        notify();
    }
}

