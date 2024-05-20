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
    for(int i = 0; i < count; i++)
        callback();
}
void ControlledClock::increment()
{
    callback();
}
void ControlledClock::setCallback(std::function<void()> _callback)
{
    callback = _callback;
}