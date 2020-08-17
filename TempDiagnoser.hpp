#ifndef TEMPDIAGNOSER_HPP
#define TEMPDIAGNOSER_HPP 1

#include "IDiagnose.hpp"
#include "IObserver.hpp"

class ITemperatureMonitor;

class TempDiagnoser : public IDiagnose
{
    class TemperatureNotifier : public IObserver
    {
    public:
        explicit TemperatureNotifier(TempDiagnoser *temperatureDiag) : notifyObject(temperatureDiag) { }
        virtual ~TemperatureNotifier() { }
        virtual void notification() { notifyObject->readTemperature(); }
    private:
        TempDiagnoser* notifyObject;
    };

public:
    TempDiagnoser();
    virtual ~TempDiagnoser();
    virtual bool getDiagnosis(std::string &diagnosis);
    virtual std::string getName() { return diagName; }
    virtual void dispatchEvents();

private:
    std::string diagName;
    float temperature;
    bool sendNotify;
    ITemperatureMonitor *tempSource;
    TemperatureNotifier tempNotifier;

    void readTemperature();

};

#endif
