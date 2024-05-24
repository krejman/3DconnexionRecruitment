#pragma once
#include <atomic>
#include <thread>
#include "Clock.hpp"

class RealClock : public Clock
{
public:
    void start();
    void stop();
    void setCallback(std::function<void()>);
    RealClock();
    void end();
private:
    void run();
    std::atomic_bool running{ false }, endClock{ false };
    std::function<void()> callback;
    std::thread thread;
};