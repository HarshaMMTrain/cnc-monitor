#ifndef PARTPRECISIONDIAGNOSER_HPP
#define PARTPRECISIONDIAGNOSER_HPP 1

#include "IDiagnose.hpp"

class PartPrecisionDiagnoser : public IDiagnose
{
public:
    PartPrecisionDiagnoser() { }
    virtual ~PartPrecisionDiagnoser() { }
    virtual int diagnose(const std::vector<DiagParam> &diagParamArray,
                         std::string &diagnosis);
};

#endif
