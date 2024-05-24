#include <iostream>
#include "CliFacade.hpp"
#include "ControlledClock.hpp"
#include "RealClock.hpp"

void CliFacade::chooseClock()
{
	std::cout << "Choose clock type:\n1: Controlled Clock\n2: Realtime clock" << std::endl;
	int choice;
	while (true)
	{
		std::cin >> choice;
		if (choice == 1 or choice == 2)
			break;
		std::cout << "\nWrong choice, type again\n";
	}
	if (choice == 1)
	{
		if (clock and realClock)
		{
			auto rClock = std::dynamic_pointer_cast<RealClock>(clock);
			rClock->end();
		}
		clock = std::make_shared<ControlledClock>();
		realClock = false;
	}
	else
	{
		auto rClock = std::make_shared<RealClock>();
		rClock->setCallback([this]() {this->notifyAboutUpdate(); });
		clock = rClock;
		realClock = true;
	}
	timerService.setClock(clock);
}

void CliFacade::controlledClockControlMenu()
{
	if (realClock)
		return;
	while(true)
	{
		std::cout << "\nChoose an operation\n1: Single increment\n2: Increment by multiple seconds\n3: Quit";
		int choice;
		while (true)
		{
			std::cin >> choice;
			if (choice > 0 and choice < 4)
				break;
			std::cout << "\nWrong choice, type again\n";
		}
		if (choice == 3)
			break;
		if (choice == 1)
			std::dynamic_pointer_cast<ControlledClock>(clock)->increment();
		if (choice == 2)
		{
			std::cout << "\nChoose how many seconds to increment\n";
			std::cin >> choice;
			std::dynamic_pointer_cast<ControlledClock>(clock)->increment(choice);
		}
	}
}

void CliFacade::printMenu() const
{
	std::cout << "CarShop main menu:\n0: add car for sell\n1: start day\n2: end day\n3: show cars for sell\n4: show sold cars raport\n5: show all cars\n6: Configure app's clock\n7: Exit app\n";
	if (not realClock)
		std::cout << "8: Control clock\n";
}

void CliFacade::run()
{
	chooseClock();
	while (true)
	{
		printMenu();
		int choice;
		while (true)
		{
			std::cin >> choice;
			if (choice >= 0 and (choice < 8 or (choice == 8 and not realClock)))
				break;
			std::cout << "\nWrong choice, type again\n";
		}
		switch (choice)
		{
			case 0:
				addCar();
				break;
			case 1:
				startDay();
				break;
			case 2:
				endDay();
				break;
			case 3:
				sellingView();
				break;
			case 4:
				soldCarsView();
				break;
			case 5:
				allCarsView();
				break;
			case 6:
				chooseClock();
				break;
			case 7:
			{
				if (realClock)
				{
					auto rClock = std::dynamic_pointer_cast<RealClock>(clock);
					rClock->end();
				}
				return;
			}
			case 8:
				controlledClockControlMenu();
				break;
		}

	}
}
void CliFacade::soldCarsView()
{
	auto soldCars = carDatabase.getSoldCars();
	std::cout << "\nnr|model|year|price|status\n";
	printCars(soldCars);
	std::cout << "Press any key to leave this view\n";
	int a;
	std::cin >> a;
}
void CliFacade::allCarsView()
{
	auto& soldCars = carDatabase.getCars();
	std::cout << "\nnr|model|year|price|status\n";
	printCars(soldCars);
	std::cout << "Press any key to leave this view\n";
	int a;
	std::cin >> a;
}
template<class Cars>
void CliFacade::printCars(Cars cars)
{
	int idx = 1;
	for (auto it = cars.begin(); it != cars.end(); it++)
	{
		std::cout << idx++ << ": ";
		printCar(*it);
		std::cout << "\n";
	}
}
void CliFacade::printCars(const std::list<CarData>& cars)
{
	int idx = 1;
	for (auto it = cars.begin(); it != cars.end(); it++)
	{
		std::cout << idx++ << ": ";
		printCar(*it);
		std::cout << "\n";
	}
}
void CliFacade::printCar(const CarData& car)
{
	std::cout << car.getModel() << " | " << car.getYear() << " | " << car.getPrice() << " | " << to_string(car.getState());
}
void CliFacade::sellingView()
{
	isInSellingView.store(true);
	auto availableCars = carDatabase.getAvailableCars();
	while (true)
	{
		system("cls");
		std::cout << "\nnr|model|year|price|status\n";
		printCars(availableCars);
		std::cout << "\n1: sell car\n2: leave this view\n";
		int choice;
		while (true)
		{
			std::cin >> choice;
			if (choice > 0 and choice < 4)
				break;
			std::cout << "\nWrong choice, type again\n";
		}
		if (choice == 2)
		{
			isInSellingView.store(false);
			return;
		}
		if (choice == 3)
			continue;
		isInSellingView.store(false);
		std::cout << "\nPlease choose car number to sell:\n";
		auto it = availableCars.begin();
		while (true)
		{
			std::cin >> choice;
			int idx = 1;
			for (it = availableCars.begin(); it != availableCars.end(); it++)
			{
				if (idx == choice)
					break;
				idx++;
			}
			if (idx == choice)
				break;
			std::cout << "\nInvalid choice, type again\n";
		}
		sellCar(*it);
		std::cout << "\nSold car: ";
		printCar(*it);
		std::cout << "\n";
		return;
	}
}

void CliFacade::sellCar(CarData& car)
{
	car.sell();
}

void CliFacade::notifyAboutUpdate()
{
	std::cout << "Notify" << std::endl;
	if (isInSellingView.load())
	{
		std::cout << "Car price has been updated, press 3 to refresh view" << std::endl;
	}
}

void CliFacade::startDay()
{
	std::cout << "\nStarting day\n";
	clock->start();
}

void CliFacade::endDay()
{
	std::cout << "\nEnding day\n";
	clock->stop();
}

void CliFacade::addCar()
{
	std::cout << "\nAdding car to shop:\n Model: ";
	std::string model;
	int year, price;
	std::cin >> model;
	std::cout << "\nFirst Registration year: ";
	std::cin >> year;
	std::cout << "\nStarting price: ";
	std::cin >> price;
	carDatabase.createCar(year, price, model);
}