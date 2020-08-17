#include "CncDiagnoser.hpp"
#include "ITemperatureMonitor.hpp"
#include "IOptimeMonitor.hpp"
#include "IPartPrecisionMonitor.hpp"
#include "ISelftestRegister.hpp"
#include "ITimer.hpp"
#include <iostream>
#include <gtest/gtest.h>

#define HOURTOSECS(hours) (hours * 60 * 60)

class CNCTest : public ::testing::Test, public IObserver
{
public:
    CNCTest():
        CNCDiag(),
        alertSignalled(false)
    {
        std::string diagnoser("default");
        tempMonitor = getTemperatureMonitor();
        partPrecisionMonitor = getPartPrecisionMonitor();
        sysTimer = getSystemTimer();
        CNCDiag.addObserver(this);
        CNCDiag.setDiagnoser(diagnoser);
    }
    void notification()
    {
        alertSignalled = true;
    }
    void setupDiagParams(const uint8_t testCode, const float temperature,
                         const float partPrecision, const float timeIncrementHrs)
    {
        setSelfTestCode(testCode);
        tempMonitor->setTemperature(temperature);
        partPrecisionMonitor->setPartPrecision(partPrecision);
        sysTimer->addTime((uint32_t)HOURTOSECS(timeIncrementHrs));
    }
    void checkResult(const bool alertStatus, const bool machineStat,
                     const bool environmentStat)
    {
        CNCDiag.dispatchEvents();
        
        ASSERT_EQ(alertStatus, alertSignalled);

        bool statusOk;
        std::string machineStatus;
        statusOk = CNCDiag.isMachineOk(machineStatus);
        std::cout << machineStatus << std::endl;
        ASSERT_EQ(machineStat, statusOk);

        std::string environmentStatus;
        statusOk = CNCDiag.isEnvironmentOk(environmentStatus);
        std::cout << environmentStatus << std::endl;
        ASSERT_EQ(environmentStat, statusOk);
    }
    virtual ~CNCTest()
    {
    }
    ITemperatureMonitor *tempMonitor;
    IPartPrecisionMonitor *partPrecisionMonitor;
    ITimer* sysTimer;
    CncDiagnoser CNCDiag;
    bool alertSignalled;
};

TEST_F(CNCTest, paramInrange)
{
    setupDiagParams(0xFF, 20.0f, 0.02f, 3.0f);
    checkResult(false, true, true);
}


TEST_F(CNCTest, selfTestFailed)
{
    setupDiagParams(0x01, 20.0f, 0.03f, 1.0f);
    checkResult(true, false, true);
}


TEST_F(CNCTest, tempratureOutofRange)
{
    setupDiagParams(0xFF, 34.0f, 0.03f, 0.20f);
    checkResult(false, true, true);
    setupDiagParams(0xFF, 36.0f, 0.03f, 0.20f);
    checkResult(false, true, true);
    sysTimer->addTime((uint32_t)HOURTOSECS(0.31f));
    checkResult(true, true, false);
}

TEST_F(CNCTest, optimehigher)
{
    setupDiagParams(0xFF, 34.0f, 0.03f, 1.35f);
    checkResult(false, true, true);
    sysTimer->addTime((uint32_t)HOURTOSECS(0.26f));
    checkResult(true, true, false);
}

TEST_F(CNCTest, precisionLow)
{
    setupDiagParams(0xFF, 34.0f, 0.06f, 0.0f);
    checkResult(true, true, false);
}

TEST_F(CNCTest, AllErrors)
{
    setupDiagParams(0x02, 41.0f, 0.06f, 6.76f);
    checkResult(true, false, false);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

