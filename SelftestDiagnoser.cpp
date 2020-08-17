#include "SelftestDiagnoser.hpp"
#include "DiagnoserRegister.hpp"
#include "ISelftestRegister.hpp"
#include <iostream>

REGISTER_TO_DIAGFACTORY(SelftestDiagnoser, "selftest")

#define SELF_TEST_CODE_OK 0xFF

SelftestDiagnoser::SelftestDiagnoser() :
    diagName("selftest")
{
    selfTestCode = getSelfTestCode();
}

SelftestDiagnoser::~SelftestDiagnoser()
{

}

bool
SelftestDiagnoser::getDiagnosis(std::string &diagnosis)
{
    bool ret = false;
    const std::vector<std::string> selfDiagnosis{std::string("selftest: No Data"),
                                                 std::string("selftest: Controller board error"),
                                                 std::string("selftest: Configuration data corrupted")};
    if (SELF_TEST_CODE_OK != selfTestCode)
    {
        if (selfTestCode >= (int)selfDiagnosis.size())
            diagnosis.assign("selftest: Unknown error");
        else
            diagnosis.assign(selfDiagnosis[selfTestCode]);
    }
    else
    {
        ret = true;
        diagnosis.assign("selftest: OK ");
    }

    return ret;
}

void
SelftestDiagnoser::dispatchEvents()
{
    selfTestCode = getSelfTestCode();
    if (SELF_TEST_CODE_OK != selfTestCode)
    {
        notify();
    }
}

