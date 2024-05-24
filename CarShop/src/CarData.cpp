#include "CarData.hpp"
#include <iostream>

void CarData::updatePrice()
{
	price -= increment;
	priceDropCount++;
	if (timer)
		std::cout << "yes";
	timer.reset();
	if (priceDropCount >= maxDropCount)
		return;
	timer = std::make_shared<Timer>(laterTimer,[this]()
		{
			return this->updatePrice();
		});
	timerService.registerNewTimer(timer);
}

void CarData::sell()
{
	timerService.releaseTimer(timer);
	timer.reset();
	state = State::SOLD;
}

std::string to_string(State state)
{
	return (state == State::SOLD) ? "sold" : "available";
}