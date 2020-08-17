#ifndef ITIMERNOTIFY_HPP
#define ITIMERNOTIFY_HPP 1

class ITimerNotify
{
public:
    ITimerNotify() { }
    virtual ~ITimerNotify() { }
    virtual void notification() = 0;
};

#endif
