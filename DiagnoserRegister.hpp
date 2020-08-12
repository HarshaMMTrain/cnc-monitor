#ifndef DIAGNOSERREGISTER_HPP
#define DIAGNOSERREGISTER_HPP 1

#include "IDiagnose.hpp"
#include "IDiagnoserAllocator.hpp"
#include <string>

template<typename T>
class DiagAlloc : public IDiagnoserAllocator
{
public:
    DiagAlloc() { }
    virtual ~DiagAlloc() { }
    virtual IDiagnose * allocDiagnoser() { return new T(); }
};

class DiagnoserRegister
{
public:
    DiagnoserRegister(const std::string &&diagnoserName, IDiagnoserAllocator *diagAlloc);
    virtual ~DiagnoserRegister() { }
};

#define REGISTER_TO_DIAGFACTORY(className, name)                 \
    static DiagAlloc<className> className##Alloc;         \
    static DiagnoserRegister regDiagnoser(std::string(name), &className##Alloc);


#endif
