#ifndef OPTIMEDIAGNOSER_HPP
#define OPTIMEDIAGNOSER_HPP 1

#include "IDiagnose.hpp"

class OptimeDiagnoser : public IDiagnose
{
public:
    OptimeDiagnoser() { }
    virtual ~OptimeDiagnoser() { }
    virtual int diagnose(const std::vector<DiagParam> &diagParamArray,
                         std::string &diagnosis);
};

#endif
