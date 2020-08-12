#ifndef SELFTESTDIAGNOSER_HPP
#define SELFTESTDIAGNOSER_HPP 1

#include "IDiagnose.hpp"

class SelftestDiagnoser : public IDiagnose
{
public:
    SelftestDiagnoser() { }
    virtual ~SelftestDiagnoser() { }
    virtual int diagnose(const std::vector<DiagParam> &diagParamArray,
                         std::string &diagnosis);
};

#endif
