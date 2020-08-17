#ifndef IOPTIMEMONITOR_HPP
#define IOPTIMEMONITOR_HPP 1
#include "ISubject.hpp"


class IOptimeMonitor : public ISubject
{
public:
    IOptimeMonitor() { }
    virtual ~IOptimeMonitor() { }
    virtual uint32_t getOptime() = 0;
};

extern IOptimeMonitor* getOptimeMonitor();

#endif
