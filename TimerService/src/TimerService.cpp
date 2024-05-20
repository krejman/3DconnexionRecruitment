#include "TimerService.hpp"

void TimerService::setClock(std::shared_ptr<Clock> _clock)
{
    clock = std::move(_clock);
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