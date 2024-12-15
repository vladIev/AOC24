#ifndef DAY10_INPUT_HPP
#define DAY10_INPUT_HPP
#include "day10_types.hpp"

#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

TopographicMap getInput(std::filesystem::path path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);
	if(!file)
	{
		throw std::runtime_error(std::format("Failed to open file {}.", path.string()));
	}

	std::string line;
	std::getline(file, line);
	const size_t mapWidth = line.size() + 2;

	TopographicMap output;
	output.reserve(mapWidth);
	output.emplace_back(mapWidth, -1);
	while(file)
	{
		std::vector<int8_t> row;
		row.reserve(mapWidth);
		row.push_back(-1);
		std::ranges::transform(line, std::back_inserter(row), [](char c) { return c - '0'; });
		row.push_back(-1);
		output.emplace_back(std::move(row));

		std::getline(file, line);
	}

	output.emplace_back(mapWidth, -1);

	return output;
}

void printMap(const TopographicMap& map)
{
	for(const auto& row : map)
	{
		std::ranges::copy(row, std::ostream_iterator<int>(std::cout));
		std::cout << "\n";
	}
}

#endif
