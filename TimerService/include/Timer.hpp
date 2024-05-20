#pragma once
#include <functional>

class Timer
{
private:
    int seconds;
    std::function<void()> callback;
public:
    Timer(int _seconds, std::function<void()> _callback) : seconds(_seconds), callback(_callback) { }
    void fire();
    int getSeconds() const
    {
        return seconds;
    }
};