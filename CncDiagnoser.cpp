#include "CncDiagnoser.hpp"
#include "DiagnoserFactory.hpp"
#include "IObserver.hpp"
#include "ITimer.hpp"
#include <iostream>

CncDiagnoser::CncDiagnoser() :
    diagnoser(""),
    machineStatus("No machine"),
    environmentStatus("Unknown"),
    diagEvtHandlers(),
    isMachineFine(true),
    isEnvironmentFine(true),
    sendNotify(false)
{

}

void
CncDiagnoser::updateDiagnosis(IDiagnose *diagModule)
{
    std::string diagStatus;
    bool isStatusOk;
    isStatusOk = diagModule->getDiagnosis(diagStatus);
    diagStatus += "\n";
    if (!isStatusOk)
    {
        if (diagModule->getName() == "selftest")
            machineStatus += diagStatus;
        else
            environmentStatus += diagStatus;
    }
}

void
CncDiagnoser::dispatchEvents()
{
    std::vector<DiagnoserEventHandler*>::iterator iter = diagEvtHandlers.begin();
    getSystemTimer()->dispatchEvents();
    machineStatus.assign("");
    environmentStatus.assign("");
    for (; iter != diagEvtHandlers.end(); ++iter)
    {
        IDiagnose *diagModule = (*iter)->getDiagnoser();
        diagModule->dispatchEvents();
        updateDiagnosis(diagModule);
    }
    if (sendNotify)
    {
        sendNotify = false;
        notify();
    }
}

CncDiagnoser::~CncDiagnoser()
{
    DiagnoserFactory *diagFactory = DiagnoserFactory::getDiagnoserFactory();
    std::vector<DiagnoserEventHandler*>::iterator iter = diagEvtHandlers.begin();
    
    for (; iter != diagEvtHandlers.end(); ++iter)
    {
        IDiagnose *diagModule = (*iter)->getDiagnoser();
        diagModule->removeObserver(*iter);
        diagFactory->putDiagnoser(diagModule);
        delete(*iter);
    }
    diagEvtHandlers.clear();
}

void
CncDiagnoser::diagnoserEvent(IDiagnose *diagnoser)
{
    std::string diagMessage;

    if (diagnoser->getName() == "selftest")
    {
        isMachineFine &= diagnoser->getDiagnosis(diagMessage);
    }
    else
    {
        isEnvironmentFine &= diagnoser->getDiagnosis(diagMessage);
    }
    sendNotify = !isMachineFine || !isEnvironmentFine;
}

int
CncDiagnoser::setDiagnoser(const std::string &diagnoserName)
{
    int ret = 0;
    DiagnoserFactory *diagFactory = DiagnoserFactory::getDiagnoserFactory();

    if (diagnoserName != diagnoser)
    {
        diagnoser = diagnoserName;

        if (diagnoserName == "default")
            ret = setupDefaultDiagnosis(diagFactory);
        else
            ret = monitorDiagnoser(diagnoser, diagFactory);
    }

    return ret;
}

int
CncDiagnoser::setupDefaultDiagnosis(DiagnoserFactory *diagFactory)
{
    std::vector<std::string> diagnoserArray;
    diagFactory->getDiagnoserArray(diagnoserArray);
    int ret = -1;

    for (auto diagModuleName : diagnoserArray)
    {
        ret = monitorDiagnoser(diagModuleName, diagFactory);
    }

    return ret;
}

int
CncDiagnoser::monitorDiagnoser(std::string &diagModuleName, DiagnoserFactory *diagFactory)
{
    IDiagnose *diagModule;
    int ret = -1;
    diagModule = diagFactory->getDiagnoser(diagModuleName);

    if (nullptr != diagModule)
    {
        DiagnoserEventHandler *evtHandler = new DiagnoserEventHandler(diagModule, this);
        diagModule->addObserver(evtHandler);
        diagEvtHandlers.push_back(evtHandler);
        ret = 0;
    }
    return ret;
}

bool
CncDiagnoser::isMachineOk(std::string &statusMessage)
{
    statusMessage = machineStatus;
    return isMachineFine;
}

bool
CncDiagnoser::isEnvironmentOk(std::string &statusMessage)
{
    statusMessage = environmentStatus;
    return isEnvironmentFine;
}
