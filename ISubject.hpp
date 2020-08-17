#ifndef ISUBJECT_HPP
#define ISUBJECT_HPP
#include "IObserver.hpp"
#include <algorithm>
#include <vector>

class ISubject
{
public:
    ISubject() :  observerArray() { }
    virtual ~ISubject()
    {
        observerArray.clear();
    }
    virtual void addObserver(IObserver *observer)
    {
        observerArray.push_back(observer);
    }
    virtual void removeObserver(IObserver *observer)
    {
        std::vector<IObserver *>::iterator iter = 
            std::find(observerArray.begin(), observerArray.end(), observer);

        if (iter != observerArray.end())
        {
            observerArray.erase(iter);
        }
    }

protected:
    virtual void notify()
    {
        for (auto& observer : observerArray)
        {
            observer->notification();
        }
    }
private:
    std::vector<IObserver*> observerArray;
};

#endif
