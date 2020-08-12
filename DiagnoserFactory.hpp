#ifndef DIAGNOSERFACTORY_HPP
#define DIAGNOSERFACTORY_HPP 1

#include "IDiagnose.hpp"
#include "IDiagnoserAllocator.hpp"
#include <map>
#include <string>

class DiagnoserFactory;

class DiagnoserFactory
{
public:
    virtual ~DiagnoserFactory() { pDiagnoserFactory =  nullptr; }
    static DiagnoserFactory* getDiagnoserFactory();
    void registerDiagnoser(const std::string &name, IDiagnoserAllocator *diagnoserAlloc);
    IDiagnose* getDiagnoser(const std::string &name);
    void getDiagnoserArray(std::vector<std::string> &diagnoserArray);
    void putDiagnoser(IDiagnose *diagnoser);
    
private:
    static DiagnoserFactory* pDiagnoserFactory;
    std::map<const std::string, IDiagnoserAllocator *> diagnoserMap;
    DiagnoserFactory() : diagnoserMap() { }
};

#endif
