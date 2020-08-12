#ifndef TEMPDIAGNOSER_HPP
#define TEMPDIAGNOSER_HPP 1

#include "IDiagnose.hpp"

class TempDiagnoser : public IDiagnose
{
public:
    TempDiagnoser() { }
    virtual ~TempDiagnoser() { }
    virtual int diagnose(const std::vector<DiagParam> &diagParamArray,
                         std::string &diagnosis);
};

#endif
