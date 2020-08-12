
#include "DiagnoserFactory.hpp"

DiagnoserFactory* DiagnoserFactory::pDiagnoserFactory = nullptr;

DiagnoserFactory*
DiagnoserFactory::getDiagnoserFactory()
{
    if (nullptr == pDiagnoserFactory)
        pDiagnoserFactory = new DiagnoserFactory();
    return pDiagnoserFactory;
}

void
DiagnoserFactory::registerDiagnoser(const std::string &name, IDiagnoserAllocator *diagnoserAlloc)
{
    diagnoserMap[name] = diagnoserAlloc;
}

IDiagnose*
DiagnoserFactory::getDiagnoser(const std::string &vName)
{
    IDiagnose* diagnoser = nullptr;
    std::map<const std::string, IDiagnoserAllocator*>::iterator iter = diagnoserMap.find(vName);

    if (iter != diagnoserMap.end())
        diagnoser = (iter->second)->allocDiagnoser();

    return diagnoser;
}

void
DiagnoserFactory::getDiagnoserArray(std::vector<std::string> &diagnoserArray)
{
    std::map<const std::string, IDiagnoserAllocator*>::iterator iter = diagnoserMap.begin();

    for (;iter != diagnoserMap.end(); ++iter)
        diagnoserArray.push_back(iter->first);
}

void
DiagnoserFactory::putDiagnoser(IDiagnose *diagnoser)
{
    delete diagnoser;
}
