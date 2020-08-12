#include "OptimeDiagnoser.hpp"
#include "DiagnoserRegister.hpp"
#include "utility.hpp"

REGISTER_TO_DIAGFACTORY(OptimeDiagnoser, "optime")

int
OptimeDiagnoser::diagnose(const std::vector<DiagParam> &diagParamArray,
                         std::string &diagnosis)
{
    float paramVal;
    int ret = getParamValue("optime", diagParamArray, paramVal);
    if (0 == ret)
    {
        if (paramVal > 6)
        {
            ret = 1;
            diagnosis.assign("optime: continuous operating time beyond the acceptable higher limit(6hrs)");
        }
        else
        {
            diagnosis.assign("optime: OK ");
        }
    }
    else
    {
        diagnosis.assign("optime: No relevant input");
    }

    return ret;
}
