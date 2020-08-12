#include "SelftestDiagnoser.hpp"
#include "DiagnoserRegister.hpp"
#include "utility.hpp"

REGISTER_TO_DIAGFACTORY(SelftestDiagnoser, "selftest")

#define SELF_TEST_CODE_OK 0xFF

int
SelftestDiagnoser::diagnose(const std::vector<DiagParam> &diagParamArray,
                            std::string &diagnosis)
{
    float paramVal;
    const std::vector<std::string> selfDiagnosis{std::string("selftest: No Data"),
                                                 std::string("selftest: Controller board error"),
                                                 std::string("selftest: Configuration data corrupted")};
    
    int ret = getParamValue("selftest", diagParamArray, paramVal);
    diagnosis.assign("selftest: No relevant input");
    if (0 == ret)
    {
        int selfTestCode = (int)(paramVal + 0.5f);

        if (SELF_TEST_CODE_OK != selfTestCode)
        {
            ret = 1;
            if (selfTestCode >= (int)selfDiagnosis.size())
                diagnosis.assign("selftest: Unknown error");
            else
                diagnosis.assign(selfDiagnosis[selfTestCode]);
        }
        else
        {
            diagnosis.assign("selftest: OK ");
        }
    }
    return ret;
}
