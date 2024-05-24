#include "TimerService.hpp"

void TimerService::setClock(std::shared_ptr<Clock> _clock)
{
    clock = std::move(_clock);
    clock->setCallback([this]() { this->secondHasPassed(); });
}
void TimerService::registerNewTimer(std::shared_ptr<Timer> _timer)
{
    int expiration = _timer->getSeconds() + currentSecond;
    LUT.emplace(_timer, expiration);
    timers.emplace(expiration, _timer);
}
void TimerService::releaseTimer(std::shared_ptr<Timer> _timer)
{
    int expiration = LUT.at(_timer);
    timers.erase(std::make_pair(expiration, _timer));
    LUT.erase(_timer);
}
void TimerService::secondHasPassed()
{
    currentSecond++;
    auto setIter = timers.begin();
    int cnt{ 0 };
    while(setIter != timers.end())
    {
        if (setIter->first > currentSecond)
            break;
        cnt++;
        setIter->second->fire();
        LUT.erase(setIter->second);
        auto nextIter = std::next(setIter);
        timers.erase(setIter);
        setIter = nextIter;
    }
    if (cnt and callback)
        callback();
}

void TimerService::setCallback(std::function<void()> _callback)
{
    callback = _callback;
}