#ifndef CNCDIAGNOSER_HPP
#define CNCDIAGNOSER_HPP 1

#include "IDiagnose.hpp"
#include <string>
#include <vector>

class CncDiagnoser
{
public:
    explicit CncDiagnoser(const unsigned int selfTestCode);
    virtual ~CncDiagnoser();
    int setDiagnoser(const std::string &diagnoserName);
    void diagnose(const std::vector<DiagParam> &diagParamArray);
    bool isMachineOk(std::string &statusMessage);
    bool isEnvironmentOk(std::string &statusMessage);
private:
    std::string diagnoser;
    std::string machineStatus;
    std::string environmentStatus;
    bool isMachineFine;
    bool isEnvironmentFine;

    bool defaultDiagnose(const std::vector<DiagParam> &diagParamArray,
                         std::string &environmentStatus);

    bool customDiagnose(const std::vector<DiagParam> &diagParamArray,
                        std::string &environmentStatus);

};

#endif

