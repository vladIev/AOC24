#include "day6_1.hpp"
#include "day6_2.hpp"
#include "day6_input.hpp"

#include <iostream>

int main()
{
	auto [obstaclesX, obstaclesY, guardPosition] =
		parseInput("/home/vladlev/projects/AOC24/inputs/day6.txt");

	auto passedCelss = d61::getPassedCells(obstaclesX, obstaclesY, guardPosition);
	std::cout << "Steps: " << passedCelss.size() << std::endl;

	auto hittedObst = countPossibleLoops(passedCelss, obstaclesX, obstaclesY, guardPosition);
	std::cout << "Possible obstacles: " << hittedObst << std::endl;

	return 0;
}