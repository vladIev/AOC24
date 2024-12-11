#ifndef DAY7_HPP
#define DAY7_HPP

#include "day7_equation.hpp"
#include <cassert>
#include <filesystem>
#include <format>
#include <fstream>
#include <iterator>
#include <string>

std::string loadFile(std::filesystem::path path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);
	if(!file)
	{
		throw std::runtime_error(std::format("Failed to open file {}.", path.string()));
	}

	return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

auto parseData(const std::string& data)
{
	std::vector<Equation> input;
	std::stringstream ss(data);
	std::string line;
	std::getline(ss, line);
	while(ss)
	{
		input.emplace_back(line);
		std::getline(ss, line);
	}
	return input;
}

auto parseInput(std::filesystem::path path)
{
	auto data = loadFile(path);
	return parseData(data);
}

#endif