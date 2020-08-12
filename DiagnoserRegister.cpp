#include "DiagnoserRegister.hpp"
#include "DiagnoserFactory.hpp"


DiagnoserRegister::DiagnoserRegister(const std::string &&diagnoserName, IDiagnoserAllocator *diagAlloc)
{
    DiagnoserFactory *pDb = DiagnoserFactory::getDiagnoserFactory();
    if (nullptr != pDb)
        pDb->registerDiagnoser(diagnoserName, diagAlloc);
}

