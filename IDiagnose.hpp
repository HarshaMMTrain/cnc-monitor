#ifndef IDIAGNOSE_HPP
#define IDIAGNOSE_HPP 1

#include "ISubject.hpp"
#include <string>
#include <vector>

class IDiagnose : public ISubject
{
public:
    IDiagnose() { }
    virtual ~IDiagnose() { }
    virtual std::string getName() = 0;
    virtual bool getDiagnosis(std::string &diagnosis) = 0;
    virtual void dispatchEvents() = 0;
};

#endif
