#include "TempDiagnoser.hpp"
#include "DiagnoserRegister.hpp"
#include "utility.hpp"

REGISTER_TO_DIAGFACTORY(TempDiagnoser, "temperature")

int
TempDiagnoser::diagnose(const std::vector<DiagParam> &diagParamArray,
                         std::string &diagnosis)
{
    float paramVal;
    int ret = getParamValue("temperature", diagParamArray, paramVal);
    diagnosis.assign("temperature: No relevant input");
    if (0 == ret)
    {
        if (paramVal > 35)
        {
            ret = 1;
            diagnosis.assign("temperature: beyond the acceptable higher limit(35degrees)");
        }
        else
        {
            diagnosis.assign("temperature: OK ");
        }
    }
    return ret;
}

