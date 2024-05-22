#pragma once
#include <functional>

class Clock
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~Clock() = 0 { };
    virtual void setCallback(std::function<void()>) = 0;
};