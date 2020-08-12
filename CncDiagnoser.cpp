#include "CncDiagnoser.hpp"
#include "DiagnoserFactory.hpp"
#include <iostream>

CncDiagnoser::CncDiagnoser(const unsigned int selfTestCode) :
    diagnoser("default"),
    machineStatus("No machine"),
    environmentStatus("Unknown"),
    isMachineFine(false),
    isEnvironmentFine(false)
{
    DiagnoserFactory *diagFactory = DiagnoserFactory::getDiagnoserFactory();
    IDiagnose* selfTestDiagnoser;
    std::string selfTestModule("selftest");
    std::vector<DiagParam> dParams{DiagParam("selftest", (float)selfTestCode)};

    selfTestDiagnoser = diagFactory->getDiagnoser(selfTestModule);
    if (nullptr != selfTestDiagnoser)
    {
        isMachineFine = (selfTestDiagnoser->diagnose(dParams, machineStatus) != 0) ? false : true;
        diagFactory->putDiagnoser(selfTestDiagnoser);
    }
}

CncDiagnoser::~CncDiagnoser()
{

}

int
CncDiagnoser::setDiagnoser(const std::string &diagnoserName)
{
    int ret = 0;
    DiagnoserFactory *diagFactory = DiagnoserFactory::getDiagnoserFactory();
    diagnoser = diagnoserName;

    if (diagnoserName != "default")
    {
        if (nullptr == diagFactory->getDiagnoser(diagnoserName))
            ret = -1;
    }

    return ret;
}

bool
CncDiagnoser::defaultDiagnose(const std::vector<DiagParam> &diagParamArray,
                              std::string &environmentStatus)
{
    DiagnoserFactory *diagFactory = DiagnoserFactory::getDiagnoserFactory();
    std::vector<std::string> diagnoserArray;
    environmentStatus.assign("");
    diagFactory->getDiagnoserArray(diagnoserArray);
    int ret = 0;

    for (auto diagModuleName : diagnoserArray)
    {
        int diagnoserRet;
        std::string diagStatus("");
        IDiagnose *diagModule;
        diagModule = diagFactory->getDiagnoser(diagModuleName);
        diagnoserRet = diagModule->diagnose(diagParamArray, diagStatus);
        diagFactory->putDiagnoser(diagModule);
        if (diagnoserRet >= 0)
            ret |= diagnoserRet;
        diagStatus += "\n";
        environmentStatus += diagStatus;
    }
    return (ret == 0);
}

bool
CncDiagnoser::customDiagnose(const std::vector<DiagParam> &diagParamArray,
                             std::string &environmentStatus)
{
    DiagnoserFactory *diagFactory = DiagnoserFactory::getDiagnoserFactory();
    std::string diagStatus("");
    IDiagnose *diagModule;
    int ret = -1;
    environmentStatus.assign("");
    
    diagModule = diagFactory->getDiagnoser(diagnoser);

    if (nullptr != diagModule)
    {
        ret = diagModule->diagnose(diagParamArray, diagStatus);
        diagFactory->putDiagnoser(diagModule);
        diagStatus += "\n";
        environmentStatus += diagStatus;
    }
    return (ret == 0);
}

void
CncDiagnoser::diagnose(const std::vector<DiagParam> &diagParamArray)
{
    if (diagnoser == "default")
        isEnvironmentFine = defaultDiagnose(diagParamArray, environmentStatus);
    else
        isEnvironmentFine = customDiagnose(diagParamArray, environmentStatus);
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
