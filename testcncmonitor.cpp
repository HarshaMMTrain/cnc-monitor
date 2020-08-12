#include "CncDiagnoser.hpp"
#include <gtest/gtest.h>

static void TestCnc(unsigned int selfTestCode, std::vector<DiagParam> &diagParamArray,
                    bool expectedMachineStatus, bool expectedEnvironmentStatus)
{
    CncDiagnoser diagCnc(selfTestCode);
    
    std::string machineStatus;
    std::string environmentStatus;
    bool statusOk;

    diagCnc.setDiagnoser("default");

    diagCnc.diagnose(diagParamArray);
    statusOk = diagCnc.isMachineOk(machineStatus);
    std::cout << machineStatus << std::endl;
    ASSERT_EQ(expectedMachineStatus, statusOk);

    statusOk = diagCnc.isEnvironmentOk(environmentStatus);
    std::cout << environmentStatus << std::endl;
    ASSERT_EQ(expectedEnvironmentStatus, statusOk);
}


TEST(CNCTest, paramInrange) {
    std::vector<DiagParam> diagParamArray{DiagParam("temperature", 20),
            DiagParam("partprecision", 0.03),
            DiagParam("optime", 4)};
    TestCnc(0xFF, diagParamArray, true, true);
}

TEST(CNCTest, selfTestFailed) {
    std::vector<DiagParam> diagParamArray{DiagParam("temperature", 20),
            DiagParam("partprecision", 0.03),
            DiagParam("optime", 4)};
    TestCnc(0x01, diagParamArray, false, true);
}


TEST(CNCTest, tempratureOutofRange) {
    std::vector<DiagParam> diagParamArray{DiagParam("temperature", 40),
            DiagParam("partprecision", 0.03),
            DiagParam("optime", 4)};
    TestCnc(0xFF, diagParamArray, true, false);
}

TEST(CNCTest, optimehigher) {
    std::vector<DiagParam> diagParamArray{DiagParam("temperature", 25),
            DiagParam("partprecision", 0.03),
            DiagParam("optime", 6.5)};
    TestCnc(0xFF, diagParamArray, true, false);
}

TEST(CNCTest, precisionLow) {
    std::vector<DiagParam> diagParamArray{DiagParam("temperature", 25),
            DiagParam("partprecision", 0.07),
            DiagParam("optime", 2)};
    TestCnc(0x02, diagParamArray, false, false);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

