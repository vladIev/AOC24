#ifndef DAY6_HPP
#define DAY6_HPP

#include <filesystem>
#include <format>
#include <fstream>
#include <string>
#include <vector>

using Obstacles = std::vector<std::vector<size_t>>;
struct Position
{
	size_t x = 0;
	size_t y = 0;

	bool operator==(const Position& other) const
	{
		return x == other.x && y == other.y;
	}
};

struct PositionHash
{
	std::size_t mapWidth;

	PositionHash(std::size_t width)
		: mapWidth(width)
	{ }

	std::size_t operator()(const Position& obj) const
	{
		return obj.y * mapWidth + obj.x;
	}
};

std::string loadMap(std::filesystem::path path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);
	if(!file)
	{
		throw std::runtime_error(std::format("Failed to open file {}.", path.string()));
	}

	return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

auto parseMap(const std::string& map) -> std::tuple<Obstacles, Obstacles, Position>
{
	Obstacles obstaclesOnX;
	Obstacles obstaclesOnY;

	const auto width = map.find('\n', 0);

	obstaclesOnY.resize(width);
	size_t rowCntr = 0;
	Position guardPosition;
	std::stringstream ss(map);
	std::string line;
	std::getline(ss, line);
	while(ss)
	{
		std::vector<size_t> rowObstacles;

		auto lastSympolPos = line.find_first_not_of(".", 0);
		while(lastSympolPos != std::string::npos)
		{
			if(line[lastSympolPos] == '#')
			{
				rowObstacles.push_back(lastSympolPos);
				obstaclesOnY[lastSympolPos].push_back(rowCntr);
			}
			else if(line[lastSympolPos] == '^')
			{
				guardPosition = Position{lastSympolPos, rowCntr};
			}
			lastSympolPos = line.find_first_not_of(".", lastSympolPos + 1);
		}

		rowCntr++;
		obstaclesOnX.emplace_back(rowObstacles);
		std::getline(ss, line);
	}
	return std::make_tuple(obstaclesOnX, obstaclesOnY, guardPosition);
}

auto parseInput(std::filesystem::path path) -> std::tuple<Obstacles, Obstacles, Position>
{
	const auto map = loadMap(path);
	return parseMap(map);
}

#endif