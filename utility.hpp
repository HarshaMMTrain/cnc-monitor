#ifndef UTILITY_HPP
#define UTILITY_HPP 1

#include "IDiagnose.hpp"
#include <string>
#include <vector>

extern int getParamValue(const std::string &paramName,
                         const std::vector<DiagParam> &diagParamArray,
                         float &paramValue);

#endif
