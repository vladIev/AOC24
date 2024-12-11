#include "day7_equation.hpp"
#include "day7_input.hpp"

#include <algorithm>
#include <iostream>

uint64_t countSolvalables(const std::span<const Equation> equations)
{
	uint64_t result{0};
	for(const auto& equation : equations)
	{
		result += equation.isSolvalable() ? equation.response : 0;
	}
	return result;
}

int main()
{
	const auto equations = parseInput("/home/vladlev/projects/AOC24/inputs/day7.txt");
	std::cout << countSolvalables(equations) << std::endl;
	//6083020304036
	return 0;
}