#ifndef CNCDIAGNOSER_HPP
#define CNCDIAGNOSER_HPP 1

#include "ISubject.hpp"
#include <string>
#include <vector>

class DiagnoserEventHandler;
class IDiagnose;
class DiagnoserFactory;

class CncDiagnoser : public ISubject
{
    class DiagnoserEventHandler : public IObserver
    {
    public:
        DiagnoserEventHandler(IDiagnose *diag, CncDiagnoser *cncDiag) :
            diagnoser(diag),
            mainDiag(cncDiag)
        {
        
        }
        virtual ~DiagnoserEventHandler() { }
        IDiagnose* getDiagnoser() { return diagnoser; }
        virtual void notification()
        {
            mainDiag->diagnoserEvent(diagnoser);
        }

    private:
        IDiagnose* diagnoser;
        CncDiagnoser* mainDiag;
    };

public:
    CncDiagnoser();
    virtual ~CncDiagnoser();
    int setDiagnoser(const std::string &diagnoserName);
    void dispatchEvents();
    bool isMachineOk(std::string &statusMessage);
    bool isEnvironmentOk(std::string &statusMessage);
private:
    std::string diagnoser;
    std::string machineStatus;
    std::string environmentStatus;
    std::vector<DiagnoserEventHandler*> diagEvtHandlers;
    bool isMachineFine;
    bool isEnvironmentFine;
    bool sendNotify;

    void diagnoserEvent(IDiagnose *diagnoser);
    int setupDefaultDiagnosis(DiagnoserFactory *diagFactory);
    int monitorDiagnoser(std::string &diagModule, DiagnoserFactory *diagFactory);
    void updateDiagnosis(IDiagnose *diagModule);
};

#endif

