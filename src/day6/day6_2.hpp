#ifndef DAY6_2_HPP
#define DAY6_2_HPP
#include "day6_1.hpp"
#include "day6_input.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace d61;
bool canLeaveMap(const auto& obstaclesX, const auto& obstaclesY, Position guardPosition)
{
	const auto mapWidth = obstaclesY.size();
	const auto mapHeight = obstaclesX.size();

	std::unordered_map<Position, std::set<Direction>, PositionHash> hittedObstacles(
		100, PositionHash(mapWidth));

	auto currentDirection = Direction::UP;
	bool isLeftMap = false;
	while(!isLeftMap)
	{
		Position newPos;
		switch(currentDirection)
		{
		case Direction::UP: {
			std::tie(newPos, isLeftMap) = goUp(obstaclesY, guardPosition);
			const auto [_, success] = hittedObstacles[newPos].insert(currentDirection);
			if(!success)
			{
				return false;
			}

			currentDirection = Direction::RIGHT;
			break;
		}
		case Direction::DOWN: {
			std::tie(newPos, isLeftMap) = goDown(obstaclesY, guardPosition, mapHeight);
			const auto [_, success] = hittedObstacles[newPos].insert(currentDirection);
			if(!success)
			{
				return false;
			}

			currentDirection = Direction::LEFT;
			break;
		}
		case Direction::LEFT: {
			std::tie(newPos, isLeftMap) = goLeft(obstaclesX, guardPosition);
			const auto [_, success] = hittedObstacles[newPos].insert(currentDirection);
			if(!success)
			{
				return false;
			}

			currentDirection = Direction::UP;
			break;
		}
		case Direction::RIGHT:
			std::tie(newPos, isLeftMap) = goRight(obstaclesX, guardPosition, mapWidth);
			const auto [_, success] = hittedObstacles[newPos].insert(currentDirection);
			if(!success)
			{
				return false;
			}

			currentDirection = Direction::DOWN;
			break;
		}
		guardPosition = newPos;
	}

	return true;
}

uint64_t countPossibleLoops(const std::unordered_set<Position, PositionHash>& passedCells,
							const Obstacles& obstaclesX,
							const Obstacles& obstaclesY,
							Position startPosition)
{
	assert(canLeaveMap(obstaclesX, obstaclesY, startPosition));
	std::unordered_set<Position, PositionHash> visitedCells(1000, obstaclesX.size());

	uint64_t cntr = 0;
	auto copyObstX = obstaclesX;
	auto copyObstY = obstaclesY;
	for(const auto& passedCell : passedCells)
	{
		if(visitedCells.contains(passedCell) || passedCell == startPosition) continue;

		auto& refX = copyObstX[passedCell.y];
		auto& refY = copyObstY[passedCell.x];
		const auto origX = refX;
		const auto origY = refY;

		// Add a new obstacle
		refX.push_back(passedCell.x);
		refY.push_back(passedCell.y);
		std::sort(refX.begin(), refX.end());
		std::sort(refY.begin(), refY.end());

		const auto canLeave = canLeaveMap(copyObstX, copyObstY, startPosition);
		cntr += !canLeave;

		// Restore original list of obstacles
		copyObstX[passedCell.y] = origX;
		copyObstY[passedCell.x] = origY;

		// No need to check the same cell twice
		visitedCells.insert(passedCell);
	}
	return cntr;
}

#endif