#include "CliFacade.hpp"
#include <iostream>

int main()
{
	CliFacade facade;
	facade.run();
	std::cout << "\nGraceful shutdown" << std::endl;
}