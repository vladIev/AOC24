#include "day5_1.hpp"
#include "day5_2.hpp"
#include "day5_input.hpp"

#include <filesystem>
#include <iostream>
#include <iterator>
#include <ranges>

int main()
{
	const auto [rules, requests] = parseInput("/home/vladlev/projects/AOC24/inputs/day5.txt");
	d51::RulesBook book(rules);
	std::cout << d51::validateRequest(requests, book) << std::endl;
	std::cout << d52::solve(requests, book) << std::endl;

	return 0;
}