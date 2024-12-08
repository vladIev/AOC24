#include <algorithm>
#include <array>
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <ranges>
#include <span>
#include <sstream>
#include <stdexcept>
#include <vector>

constexpr uint8_t NUM_LEVELS = 5;
using Levels = std::vector<int32_t>;
std::vector<Levels> parseInput(std::filesystem::path path)
{
	std::vector<Levels> output;
	std::ifstream file(path);
	if(!file)
	{
		throw std::runtime_error(std::format("Failed to open file {}.", path.string()));
	}

	std::string line;
	while(std::getline(file, line))
	{
		output.emplace_back();
		auto levelsIt = output.rbegin();
		std::stringstream stream(line);
		while(1)
		{
			int32_t value = 0;
			stream >> value;
			if(!stream)
			{
				break;
			}
			levelsIt->push_back(value);
		}
	}
	return output;
}

bool isLevelSafe(const std::vector<int32_t>& levels, bool protection)
{
	const bool isAscending =
		levels[0] < levels[1] && levels[0] < levels[2] ? true : levels[1] < levels[2];
	const int mult = isAscending ? 1 : -1;
	for(auto i = 1; i < levels.size(); i++)
	{
		const int diff = mult * (levels[i] - levels[i - 1]);
		if(diff >= 1 && diff <= 3)
		{
			continue;
		}
		if(protection)
		{
			for(int j = i - 1; j <= i; j++)
			{
				auto copy = levels;
				copy.erase(std::next(std::begin(copy), j));
				if(isLevelSafe(copy, false);)
				{
					return true;
				}
			}

			return false;
		}
		return false;
	}
	return true;
}

auto main(int argc, char** argv) -> int
{
	auto input = parseInput("/home/vladlev/projects/AOC24/inputs/day2.txt");
	auto result =
		std::count_if(input.begin(), input.end(), [](auto& el) { return isLevelSafe(el, true); });

	std::cout << result << std::endl;

	return 0;
}