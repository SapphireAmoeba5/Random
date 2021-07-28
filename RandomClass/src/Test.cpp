#include <random>
#include <iostream>

#include "Random.h"

int main()
{
	Random random(1, 1000);
	auto number = random();

	std::cout << number << "\n";
}