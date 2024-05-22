#include <functional>
#include <ranges>
#include <vector>
#include "CarData.hpp"

class CarDatabase
{
	auto getAvailableCars()
	{
		return cars | std::ranges::views::filter([](CarData& car){ return car.getState() == State::AVAILABLE; }); 
	}
	auto getSoldCars()
	{
		return cars | std::ranges::views::filter([](CarData& car) { return car.getState() == State::SOLD; });
	}
	auto getCarsUnderPrice(int price)
	{
		return cars | std::ranges::views::filter([price](CarData& car) { return car.getPrice() <= price; });
	}
	auto getCarsAfterYear(int year)
	{
		return cars | std::ranges::views::filter([year](CarData& car) { return car.getYear() >= year; });
	}
	auto getCarsCustomPredicate(std::function<bool(CarData&)> pred)
	{
		return cars | std::ranges::views::filter(pred);
	}
private:
	std::vector<CarData> cars;
};