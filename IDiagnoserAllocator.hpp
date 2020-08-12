#ifndef IDIAGNOSERALLOCATOR_HPP
#define IDIAGNOSERALLOCATOR_HPP 1

class IDiagnoserAllocator
{
public:
    IDiagnoserAllocator() { }
    virtual ~IDiagnoserAllocator() { };
    virtual IDiagnose * allocDiagnoser(void) = 0;
};

#endif
