#ifndef DAY8_HPP
#define DAY8_HPP

#include <cassert>
#include <iostream>
#include <span>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Point
{
	int x;
	int y;

	bool operator==(const Point& other) const
	{
		return x == other.x && y == other.y;
	}
};

template <size_t MapSize>
struct PointHasher
{

	std::size_t operator()(const Point& obj) const
	{
		return obj.y * MapSize + obj.x;
	}
};

using Points = std::vector<Point>;

template <size_t MapSize>
using NodesT = std::unordered_set<Point, PointHasher<MapSize>>;

using Antennas = std::unordered_map<char, Points>;

Antennas parseTable(std::span<const std::string_view> table)
{
	Antennas antennas;

	for(int y = 0; y < table.size(); ++y)
	{
		std::string_view row = table[y];
		for(int x = 0; x < row.size(); ++x)
		{
			char c = row[x];
			if(c != '.')
			{
				antennas[c].push_back(Point{x, y});
			}
		}
	}

	return antennas;
}

void drawMap(const Antennas& antennas, const auto& nodes, int mapSize)
{
	std::vector<std::string> map;
	map.resize(mapSize);
	for(auto& row : map)
	{
		row.assign(mapSize, '.');
	}

	for(const auto& [antenna_type, points] : antennas)
	{
		for(const auto& point : points)
		{
			map[point.y][point.x] = antenna_type;
		}
	}

	for(const auto& point : nodes)
	{
		map[point.y][point.x] = '#';
	}

	std::string fullMap;
	for(const auto& row : map)
	{
		fullMap += row + '\n';
	}

	std::cout << fullMap << std::endl;
}

#endif