#pragma once
#include "Clock.hpp"

class ControlledClock : Clock
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