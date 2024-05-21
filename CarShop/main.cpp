#include "TimerService.hpp"
#include "ControlledClock.hpp"
#include <iostream>

int main()
{
	TimerService timerService;
	auto clock = std::make_shared<ControlledClock>();
	timerService.setClock(clock);
	timerService.registerNewTimer(std::make_shared<Timer>(1, []() { std::cout << "test1" << std::endl; }));
	timerService.registerNewTimer(std::make_shared<Timer>(3, []() { std::cout << "test2" << std::endl; }));
	while (std::getchar() != 'a')
	{
		std::cout << "dupa" << std::endl;
		clock->increment();
	}
}