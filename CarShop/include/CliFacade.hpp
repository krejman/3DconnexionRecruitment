#pragma once
#include "CarDatabase.hpp"
#include "Clock.hpp"
#include "TimerService.hpp"

class CliFacade
{
public:
	void notifyAboutUpdate();
	void run();
	CliFacade() : timerService(), carDatabase(timerService) 
	{ 
		timerService.setCallback([this](){ this->notifyAboutUpdate(); }); 
	}
private:
	void printCar(const CarData&);
	template<class Cars>
	void printCars(Cars);
	void printCars(const std::list<CarData>&);
	void printMenu() const;
	void sellCar(CarData&);
	void sellingView();
	void endDay();
	void startDay();
	void chooseClock();
	void controlledClockControlMenu();
	void soldCarsView();
	void allCarsView();
	void addCar();
	TimerService timerService;
	CarDatabase carDatabase;
	std::shared_ptr<Clock> clock;
	bool realClock{ false };
	std::atomic_bool isInSellingView{ false };
};