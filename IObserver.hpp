#ifndef IOBSERVER_HPP
#define IOBSERVER_HPP

class IObserver
{
public:
    IObserver() { }
    virtual ~IObserver() { }
    virtual void notification() = 0;
};

#endif

