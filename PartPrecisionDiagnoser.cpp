#include "PartPrecisionDiagnoser.hpp"
#include "DiagnoserRegister.hpp"
#include "utility.hpp"

REGISTER_TO_DIAGFACTORY(PartPrecisionDiagnoser, "partprecision")

int
PartPrecisionDiagnoser::diagnose(const std::vector<DiagParam> &diagParamArray,
                                 std::string &diagnosis)
{
    float paramVal;
    int ret = getParamValue("partprecision", diagParamArray, paramVal);
    diagnosis.assign("partprecision: No relevant input");
    if (0 == ret)
    {
        if (paramVal > 0.05)
        {
            ret = 1;
            diagnosis.assign("partprecision: beyond the acceptable higher limit(0.05mm)");
        }
        else
        {
            diagnosis.assign("partprecision: OK ");
        }
    }
    return ret;
}
