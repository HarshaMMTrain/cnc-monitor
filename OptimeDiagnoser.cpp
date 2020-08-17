#include "OptimeDiagnoser.hpp"
#include "DiagnoserRegister.hpp"
#include "IOptimeMonitor.hpp"

REGISTER_TO_DIAGFACTORY(OptimeDiagnoser, "optime")

#define HOURSTOSECS(hours) (hours * 60 * 60)

OptimeDiagnoser::OptimeDiagnoser() :
    diagName("optime"),
    optime(0.0),
    sendNotify(false),
    optimeNotifier(this)
{
    optimeSource = getOptimeMonitor();
    optimeSource->addObserver(&optimeNotifier);
}

OptimeDiagnoser::~OptimeDiagnoser()
{
    optimeSource->removeObserver(&optimeNotifier);
}

void
OptimeDiagnoser::readOptime()
{
    optime = optimeSource->getOptime();
    if (optime > (uint32_t)HOURSTOSECS(6))
    {
        sendNotify = true;
    }
}

bool
OptimeDiagnoser::getDiagnosis(std::string &diagnosis)
{
    bool ret = false;
    if (optime > (uint32_t)HOURSTOSECS(6))
    {
        diagnosis.assign("optime: continuous operating time beyond the acceptable higher limit(6hrs)");
    }
    else
    {
        ret = true;
        diagnosis.assign("optime: OK ");
    }
    return ret;
}

void
OptimeDiagnoser::dispatchEvents()
{
    if (sendNotify)
    {
        sendNotify = false;
        notify();
    }
}


