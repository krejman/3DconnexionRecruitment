#pragma once
#include <string>
#include <memory>
#include "TimerService.hpp"

enum class State
{
    SOLD,
    AVAILABLE
};

class CarData
{
public:
    CarData(int _year, int _price, std::string _model, TimerService& _timerService) : year(_year), price(_price), model(_model),
        increment(price / 1000), state(State::AVAILABLE), priceDropCount(0), timerService(_timerService)
    {
        timer = std::make_shared<Timer>(firstTimer, [this]()
        {
            return this->updatePrice();
        });
        timerService.registerNewTimer(timer);
    }
    void updatePrice();
    void sell();
    int getYear() const
    {
        return year;
    }
    int getPrice() const
    {
        return price;
    }
    std::string getModel() const
    {
        return model;
    }
    State getState() const
    {
        return state;
    }
private:
    State state;
    const int year;
    const int increment;
    int price;
    int priceDropCount;
    const std::string model;
    const static int firstTimer{30}, laterTimer{10}, maxDropCount{200};
    TimerService& timerService;
    std::shared_ptr<Timer> timer;
};