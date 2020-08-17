#include "OptimeMonitor.hpp"

static IOptimeMonitor * optimeMonitor = nullptr;

IOptimeMonitor* getOptimeMonitor()
{
    if (nullptr == optimeMonitor)
        optimeMonitor = new OptimeMonitor();

    return optimeMonitor;
}

