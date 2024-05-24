#pragma once
#include <map>
#include <memory>
#include <set>
#include "Clock.hpp"
#include "Timer.hpp"

class TimerService
{
struct setComparator{
    bool operator() (const std::pair<int, std::shared_ptr<Timer>>& lhs, const std::pair<int, std::shared_ptr<Timer>>& rhs) const
    {
        if(lhs.first == rhs.first)
            return lhs.second < rhs.second;
        return lhs.first < rhs.first;
    }
};
using TimerList = std::set<std::pair<int, std::shared_ptr<Timer>>, setComparator>;
public:
    void registerNewTimer(std::shared_ptr<Timer>);
    void releaseTimer(std::shared_ptr<Timer>);
    void secondHasPassed();
    void setClock(std::shared_ptr<Clock>);
    void setCallback(std::function<void()>);
private:
    std::shared_ptr<Clock> clock;
    int currentSecond{0};
    TimerList timers;
    std::map<std::shared_ptr<Timer>, int> LUT;
    std::function<void()> callback;
};