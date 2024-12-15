#ifndef DAY10_TYPES_HPP
#define DAY10_TYPES_HPP
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Direction
{
	int dx;
	int dy;
};

struct Position
{
	size_t x = 0;
	size_t y = 0;

	bool operator==(const Position& other) const
	{
		return x == other.x && y == other.y;
	}
};

inline Position operator+(const Position& position, const Direction& direction)
{
	return {.x = position.x + direction.dx, .y = position.y + direction.dy};
}

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

using Score = uint64_t;
using Rating = uint64_t;
using Height = int8_t;
using TopographicMap = std::vector<std::vector<Height>>;
using PositionsSet = std::unordered_set<Position, PositionHash>;
using ReachableSummits = std::unordered_map<Position, PositionsSet, PositionHash>;
using TrailsRatings = std::unordered_map<Position, Rating, PositionHash>;

#endif
