#include "utility.hpp"

int
getParamValue(const std::string &paramName,
              const std::vector<DiagParam> &diagParamArray,
              float &paramValue)
{
    std::vector<DiagParam>::const_iterator iter = diagParamArray.begin();
    int ret = -1;

    for (;(iter != diagParamArray.end()) && (0 != ret); ++iter)
    {
        if (paramName == iter->paramName())
        {
            paramValue = iter->paramValue();
            ret = 0;
        }
    }
    return ret;    
}
