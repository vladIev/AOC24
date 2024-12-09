#ifndef DAY6_2_HPP
#define DAY6_2_HPP
#include "day6_input.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

bool canLeaveMap(const auto& obstaclesX, const auto& obstaclesY, Position guardPosition)
{
	const auto mapWidth = obstaclesY.size();
	const auto mapHeight = obstaclesX.size();

	std::unordered_map<Position, std::set<Direction>, PositionHash> hittedObstacles(
		100, PositionHash(mapWidth));

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
			const auto [_, success] =
				hittedObstacles[Position{.x = guardPosition.x, .y = posY}].insert(currentDirection);
			if(!success)
			{
				return false;
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
			const auto [_, success] =
				hittedObstacles[Position{.x = guardPosition.x, .y = posY}].insert(currentDirection);
			if(!success)
			{
				return false;
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
			const auto [_, success] =
				hittedObstacles[Position{.x = posX, .y = guardPosition.y}].insert(currentDirection);
			if(!success)
			{
				return false;
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
			const auto [_, success] =
				hittedObstacles[Position{.x = posX, .y = guardPosition.y}].insert(currentDirection);
			if(!success)
			{
				return false;
			}

			guardPosition.x = posX;
			currentDirection = Direction::DOWN;
			break;
		}
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
	for(const auto passedCell : passedCells)
	{
		if(visitedCells.contains(passedCell) || passedCell == startPosition) continue;

		auto& refX = copyObstX[passedCell.y];
		auto& refY = copyObstY[passedCell.x];
		const auto origX = refX;
		const auto origY = refY;

		refX.push_back(passedCell.x);
		refY.push_back(passedCell.y);
		std::sort(refX.begin(), refX.end());
		std::sort(refY.begin(), refY.end());
		const auto canLeave = canLeaveMap(copyObstX, copyObstY, startPosition);

		cntr += !canLeave;

		copyObstX[passedCell.y] = origX;
		copyObstY[passedCell.x] = origY;
		visitedCells.insert(passedCell);
	}
	return cntr;
}

#endif