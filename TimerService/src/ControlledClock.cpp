#include "ControlledClock.hpp"

void ControlledClock::start()
{
    running = true;
}
void ControlledClock::stop()
{
    running = false;
}
void ControlledClock::increment(int count)
{
    if(running)
        for(int i = 0; i < count; i++)
            callback();
}
void ControlledClock::increment()
{
    if (running)
        callback();
}
void ControlledClock::setCallback(std::function<void()> _callback)
{
    callback = _callback;
}