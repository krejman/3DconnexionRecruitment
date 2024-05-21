#pragma once
#include <functional>

class Clock
{
public:
    inline Clock() { };
    virtual void start() { };
    virtual void stop() { };
    virtual ~Clock() = 0 { };
    virtual void setCallback(std::function<void()>) { };
};