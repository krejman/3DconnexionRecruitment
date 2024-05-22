#include "CarData.hpp"

void CarData::updatePrice()
{
	price -= increment;
	priceDropCount++;
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