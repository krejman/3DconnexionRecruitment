#pragma once
#include "Clock.hpp"

class ControlledClock : public Clock
{
public:
    void start();
    void stop();
    void increment(int);
    void increment();
    void setCallback(std::function<void()>);
private:
    bool running{false};
    std::function<void()> callback;
};