#include "CarDatabase.hpp"

void CarDatabase::createCar(int year, int price, std::string& model)
{
	cars.emplace_back(year, price, model, timerService);
}