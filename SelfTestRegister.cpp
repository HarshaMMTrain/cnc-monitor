#include "ISelftestRegister.hpp"

static uint8_t selfTestCode = 0xFF;
void setSelfTestCode(uint8_t code)
{
    selfTestCode = code;
}
uint8_t getSelfTestCode()
{
    return selfTestCode;
}
