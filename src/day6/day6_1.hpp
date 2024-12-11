#ifndef DAY6_1_HPP
#define DAY6_1_HPP

#include "day6_input.hpp"

#include <iterator>
#include <ranges>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace d61
{

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

inline auto goUp(const Obstacles& obstaclesY,
				 const Position& guardPosition) -> std::pair<Position, bool>
{
	auto it = std::crbegin(obstaclesY[guardPosition.x]);
	const auto end = std::crend(obstaclesY[guardPosition.x]);
	while(it != end && *it > guardPosition.y)
	{
		++it;
	}

	const size_t finalPosOnY = it == end ? 0 : (*it + 1);
	const bool isGuardLeftMap = it == end;
	return std::make_pair(Position{.x = guardPosition.x, .y = finalPosOnY}, isGuardLeftMap);
}

inline auto goDown(const Obstacles& obstaclesY,
				   const Position& guardPosition,
				   size_t mapHeight) -> std::pair<Position, bool>
{
	auto it = std::cbegin(obstaclesY[guardPosition.x]);
	const auto end = std::cend(obstaclesY[guardPosition.x]);
	while(it != end && *it < guardPosition.y)
	{
		++it;
	}

	const size_t finalPosOnY = it == end ? mapHeight - 1 : (*it - 1);
	const bool isGuardLeftMap = it == end;
	return std::make_pair(Position{.x = guardPosition.x, .y = finalPosOnY}, isGuardLeftMap);
}

inline auto goLeft(const Obstacles& obstaclesX,
				   const Position& guardPosition) -> std::pair<Position, bool>
{
	const auto end = std::crend(obstaclesX[guardPosition.y]);
	auto it = std::crbegin(obstaclesX[guardPosition.y]);
	while(it != end && *it > guardPosition.x)
	{
		++it;
	}

	const size_t finalPosOnX = it == end ? 0 : (*it + 1);
	const bool isGuardLeftMap = it == end;
	return std::make_pair(Position{.x = finalPosOnX, .y = guardPosition.y}, isGuardLeftMap);
}

inline auto goRight(const Obstacles& obstaclesX,
					const Position& guardPosition,
					size_t mapWidth) -> std::pair<Position, bool>
{
	const auto end = std::cend(obstaclesX[guardPosition.y]);
	auto it = std::cbegin(obstaclesX[guardPosition.y]);
	while(it != end && *it < guardPosition.x)
	{
		++it;
	}

	const size_t finalPosOnX = it == end ? mapWidth - 1 : (*it - 1);
	const bool isGuardLeftMap = it == end;
	return std::make_pair(Position{.x = finalPosOnX, .y = guardPosition.y}, isGuardLeftMap);
}

inline auto getPassedCells(const auto& obstaclesX,
						   const auto& obstaclesY,
						   Position guardPosition) -> std::unordered_set<Position, PositionHash>
{
	const auto mapWidth = obstaclesY.size();
	const auto mapHeight = obstaclesX.size();

	std::unordered_set<Position, PositionHash> passedCells(
		static_cast<size_t>(mapWidth * mapHeight * 0.2), PositionHash(mapWidth));

	auto currentDirection = Direction::UP;
	bool isLeftMap = false;

	while(!isLeftMap)
	{
		Position newPos;
		switch(currentDirection)
		{
		case Direction::UP: {
			std::tie(newPos, isLeftMap) = goUp(obstaclesY, guardPosition);
			for(const auto coord : std::views::iota(newPos.y, guardPosition.y + 1))
			{
				passedCells.insert(Position{.x = guardPosition.x, .y = coord});
			}

			currentDirection = Direction::RIGHT;
			break;
		}
		case Direction::DOWN: {
			std::tie(newPos, isLeftMap) = goDown(obstaclesY, guardPosition, mapHeight);
			for(const auto coord : std::views::iota(guardPosition.y, newPos.y + 1))
			{
				passedCells.insert(Position{.x = guardPosition.x, .y = coord});
			}

			currentDirection = Direction::LEFT;
			break;
		}
		case Direction::LEFT: {
			std::tie(newPos, isLeftMap) = goLeft(obstaclesX, guardPosition);
			for(const auto coord : std::views::iota(newPos.x, guardPosition.x + 1))
			{
				passedCells.insert(Position{.x = coord, .y = guardPosition.y});
			}

			currentDirection = Direction::UP;
			break;
		}
		case Direction::RIGHT:
			std::tie(newPos, isLeftMap) = goRight(obstaclesX, guardPosition, mapWidth);
			for(const auto coord : std::views::iota(guardPosition.x, newPos.x + 1))
			{
				passedCells.insert(Position{.x = coord, .y = guardPosition.y});
			}
			currentDirection = Direction::DOWN;
			break;
		}

		guardPosition = newPos;
	}

	return passedCells;
}
} // namespace d61

#endif
