#ifndef DAY6_1_HPP
#define DAY6_1_HPP

#include "day6_input.hpp"

#include <iterator>
#include <ranges>
#include <unordered_map>
#include <unordered_set>

namespace d61
{
auto getPassedCelss(const auto& obstaclesX,
					const auto& obstaclesY,
					Position guardPosition) -> std::unordered_set<Position, PositionHash>
{

	const auto mapWidth = obstaclesY.size();
	const auto mapHeight = obstaclesX.size();
	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	std::unordered_set<Position, PositionHash> passedCells(
		static_cast<size_t>(mapWidth * mapHeight * 0.2), PositionHash(mapWidth));
	auto currentDirection = Direction::UP;
	bool isGuardLeftMap = false;
	while(!isGuardLeftMap)
	{
		switch(currentDirection)
		{
		case Direction::UP: {
			auto it = std::crbegin(obstaclesY[guardPosition.x]);
			auto end = std::crend(obstaclesY[guardPosition.x]);
			while(it != end && *it > guardPosition.y)
			{
				++it;
			}

			size_t posY = it == end ? 0 : (*it + 1);
			isGuardLeftMap = it == end;
			for(auto coord : std::views::iota(posY, guardPosition.y + 1))
			{
				passedCells.insert(Position{.x = guardPosition.x, .y = coord});
			}

			guardPosition.y = posY;
			currentDirection = Direction::RIGHT;
			break;
		}
		case Direction::DOWN: {
			const auto end = std::cend(obstaclesY[guardPosition.x]);
			auto it = std::cbegin(obstaclesY[guardPosition.x]);
			while(it != end && *it < guardPosition.y)
			{
				++it;
			}

			size_t posY = it == end ? mapHeight - 1 : (*it - 1);
			isGuardLeftMap = it == end;
			for(auto coord : std::views::iota(guardPosition.y, posY + 1))
			{
				passedCells.insert(Position{.x = guardPosition.x, .y = coord});
			}

			guardPosition.y = posY;
			currentDirection = Direction::LEFT;
			break;
		}
		case Direction::LEFT: {
			const auto end = std::crend(obstaclesX[guardPosition.y]);
			auto it = std::crbegin(obstaclesX[guardPosition.y]);
			while(it != end && *it > guardPosition.x)
			{
				++it;
			}

			size_t posX = it == end ? 0 : (*it + 1);
			isGuardLeftMap = it == end;
			for(auto coord : std::views::iota(posX, guardPosition.x + 1))
			{
				passedCells.insert(Position{.x = coord, .y = guardPosition.y});
			}

			guardPosition.x = posX;
			currentDirection = Direction::UP;
			break;
		}
		case Direction::RIGHT:
			const auto end = std::cend(obstaclesX[guardPosition.y]);
			auto it = std::cbegin(obstaclesX[guardPosition.y]);
			while(it != end && *it < guardPosition.x)
			{
				++it;
			}

			size_t posX = it == end ? mapWidth - 1 : (*it - 1);
			isGuardLeftMap = it == end;
			for(auto coord : std::views::iota(guardPosition.x, posX + 1))
			{
				passedCells.insert(Position{.x = coord, .y = guardPosition.y});
			}

			guardPosition.x = posX;
			currentDirection = Direction::DOWN;
			break;
		}
	}

	return passedCells;
}
} // namespace d61

#endif
