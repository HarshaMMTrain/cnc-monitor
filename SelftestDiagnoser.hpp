#ifndef SELFTESTDIAGNOSER_HPP
#define SELFTESTDIAGNOSER_HPP 1

#include "IDiagnose.hpp"

class SelftestDiagnoser : public IDiagnose
{
public:
    SelftestDiagnoser();
    virtual ~SelftestDiagnoser();
    virtual bool getDiagnosis(std::string &diagnosis);
    virtual std::string getName() { return diagName; }
    virtual void dispatchEvents();
private:
    std::string diagName;
    uint8_t selfTestCode;
};

#endif
