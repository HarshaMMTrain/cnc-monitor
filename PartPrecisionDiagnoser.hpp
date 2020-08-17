#ifndef PARTPRECISIONDIAGNOSER_HPP
#define PARTPRECISIONDIAGNOSER_HPP 1

#include "IDiagnose.hpp"
#include "IObserver.hpp"

class IPartPrecisionMonitor;

class PartPrecisionDiagnoser : public IDiagnose
{
    class PartPrecisionNotifier : public IObserver
    {
    public:
        explicit PartPrecisionNotifier(PartPrecisionDiagnoser *precisionDiag) : notifyObject(precisionDiag) { }
        virtual ~PartPrecisionNotifier() { }
        virtual void notification() { notifyObject->readPartPrecision(); }
    private:
        PartPrecisionDiagnoser* notifyObject;
    };

public:
    PartPrecisionDiagnoser();
    virtual ~PartPrecisionDiagnoser();
    virtual bool getDiagnosis(std::string &diagnosis);
    virtual std::string getName() { return diagName; }
    virtual void dispatchEvents();
private:
    std::string diagName;
    float partPrecision;
    bool sendNotify;
    IPartPrecisionMonitor *partPrecisionSource;
    PartPrecisionNotifier partPrecisionNotifier;

    void readPartPrecision();

};

#endif
