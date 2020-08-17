#include "TempDiagnoser.hpp"
#include "DiagnoserRegister.hpp"
#include "ITemperatureMonitor.hpp"

REGISTER_TO_DIAGFACTORY(TempDiagnoser, "temperature")

TempDiagnoser::TempDiagnoser() :
    diagName("temperature"),
    temperature(0.0),
    sendNotify(false),
    tempNotifier(this)
{
    tempSource = getTemperatureMonitor();
    tempSource->addObserver(&tempNotifier);
}

TempDiagnoser::~TempDiagnoser()
{
    tempSource->removeObserver(&tempNotifier);
}

void
TempDiagnoser::readTemperature()
{
    temperature = tempSource->getTemperature();
    if (temperature > 35)
    {
        sendNotify = true;
    }
}

bool
TempDiagnoser::getDiagnosis(std::string &diagnosis)
{
    bool ret = false;
    if (temperature > 35)
    {
        diagnosis.assign("temperature: beyond the acceptable higher limit(35degrees)");
    }
    else
    {
        ret = true;
        diagnosis.assign("temperature: OK ");
    }
    return ret;
}

void
TempDiagnoser::dispatchEvents()
{
    if (sendNotify)
    {
        sendNotify = false;
        notify();
    }
}
