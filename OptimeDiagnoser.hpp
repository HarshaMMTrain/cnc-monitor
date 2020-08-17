#ifndef OPTIMEDIAGNOSER_HPP
#define OPTIMEDIAGNOSER_HPP 1

#include "IDiagnose.hpp"
#include "IObserver.hpp"

class IOptimeMonitor;

class OptimeDiagnoser : public IDiagnose
{
    class OptimeNotifier : public IObserver
    {
    public:
        explicit OptimeNotifier(OptimeDiagnoser *optimeDiag) : notifyObject(optimeDiag) { }
        virtual ~OptimeNotifier() { }
        virtual void notification() { notifyObject->readOptime(); }
    private:
        OptimeDiagnoser* notifyObject;
    };

public:
    OptimeDiagnoser();
    virtual ~OptimeDiagnoser();
    virtual bool getDiagnosis(std::string &diagnosis);
    virtual std::string getName() { return diagName; }
    virtual void dispatchEvents();
private:
    std::string diagName;
    uint32_t optime;
    bool sendNotify;
    IOptimeMonitor *optimeSource;
    OptimeNotifier optimeNotifier;

    void readOptime();

};

#endif
