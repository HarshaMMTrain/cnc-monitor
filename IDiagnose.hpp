#ifndef IDIAGNOSE_HPP
#define IDIAGNOSE_HPP 1

#include <string>
#include <vector>

class DiagParam
{
public:
    DiagParam(const std::string &&paramName, const float &paramVal):
        diagParamName(paramName),
        diagParamValue(paramVal) { }
    DiagParam(const std::string &paramName, const float &paramVal):
        diagParamName(paramName),
        diagParamValue(paramVal) { }
    virtual ~DiagParam() { }
    const std::string & paramName() const { return diagParamName; }
    float paramValue() const { return diagParamValue; }
private:
    std::string diagParamName;
    float       diagParamValue;
};
    
class IDiagnose
{
public:
    IDiagnose() { }
    virtual ~IDiagnose() { }
    virtual int diagnose(const std::vector<DiagParam> &diagParamArray,
                         std::string &diagnosis) = 0;
};

#endif
