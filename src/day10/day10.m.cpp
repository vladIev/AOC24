
#include "day10_input.hpp"
#include "day10_types.hpp"

#include <iterator>
#include <ranges>
#include <unordered_map>
#include <unordered_set>

const Height OUT_OF_MAP = -1;
const Height SUMMIT = 9;
class RoutesFinder
{
	const size_t mapWidth;
	ReachableSummits d_cache;
	TrailsRatings d_trailsCache;
	PositionsSet d_searchInProgress;

	const TopographicMap& d_map;
	const std::array<Direction, 4> d_directions{
		Direction{.dx = 0, .dy = -1},
		Direction{.dx = -1, .dy = 0},
		Direction{.dx = 1, .dy = 0},
		Direction{.dx = 0, .dy = 1},
	};

	void searchForSummits(Position position, Height requiredHeight, PositionsSet& reachableSummits)
	{
		const Height currenHeight = d_map[position.y][position.x];
		if(currenHeight != requiredHeight) return;

		if(d_searchInProgress.contains(position)) return;

		if(currenHeight == SUMMIT)
		{
			reachableSummits.emplace(std::move(position));
			return;
		}

		if(d_cache.contains(position))
		{
			for(Position summitPos : d_cache.at(position))
			{
				reachableSummits.emplace(std::move(summitPos));
			}
			return;
		}

		d_searchInProgress.insert(position);
		PositionsSet localReachableSummits(100, PositionHash(mapWidth));
		for(const auto& direction : d_directions)
		{
			const auto neighborPos = position + direction;
			searchForSummits(neighborPos, currenHeight + 1, localReachableSummits);
		}
		d_searchInProgress.erase(position);

		d_cache.insert({position, std::move(localReachableSummits)});
		for(Position summitPos : d_cache.at(position))
		{
			reachableSummits.emplace(std::move(summitPos));
		}

		return;
	}

	Rating calculatePositionRating(Position position, Height currenHeight)
	{
		Rating localRating = 0;
		for(const auto& direction : d_directions)
		{
			const auto neighborPos = position + direction;
			localRating += getRating(neighborPos, currenHeight + 1);
		}
		return localRating;
	}

	Rating getRating(Position position, Height requiredHeight)
	{
		const Height currenHeight = d_map[position.y][position.x];
		if(currenHeight != requiredHeight) return 0; // Wrong height

		// Already in stack trace
		if(d_searchInProgress.contains(position)) return 0;
		// Route end
		if(currenHeight == SUMMIT) return 1;

		// Already in cache, no need to calculate again
		if(d_trailsCache.contains(position)) return d_trailsCache.at(position);

		d_searchInProgress.insert(position);

		auto positionRating = calculatePositionRating(position, currenHeight);
		d_searchInProgress.erase(position);

		d_trailsCache.insert({position, positionRating});

		return positionRating;
	}

  public:
	RoutesFinder(const TopographicMap& map)
		: mapWidth(map.at(0).size())
		, d_cache(1000, PositionHash(mapWidth))
		, d_trailsCache(1000, PositionHash(mapWidth))
		, d_searchInProgress(1000, PositionHash(mapWidth))
		, d_map(map)
	{ }

	const PositionsSet& searchForSummits(Position position)
	{
		if(d_cache.contains(position)) return d_cache.at(position);

		d_searchInProgress.insert(position);
		PositionsSet reachableSummits(1000, PositionHash(mapWidth));
		for(const auto& direction : d_directions)
		{
			const auto neighborPos = position + direction;
			searchForSummits(neighborPos, 1, reachableSummits);
		}
		d_searchInProgress.erase(position);

		d_cache.insert({position, std::move(reachableSummits)});
		return d_cache.at(position);
	}

	Rating calculateRating(Position position)
	{
		if(d_trailsCache.contains(position)) return d_trailsCache.at(position);

		Rating rating = 0;
		d_searchInProgress.insert(position);
		for(const auto& direction : d_directions)
		{
			const auto neighborPos = position + direction;
			rating += getRating(neighborPos, 1);
		}
		d_searchInProgress.erase(position);

		d_trailsCache.insert({position, rating});
		return rating;
	}
};

int main()
{
	const auto input = getInput("/home/vladlev/projects/AOC24/inputs/day10.txt");
	printMap(input);

	RoutesFinder finder(input);
	{
		Score totalScore = 0;
		for(const auto [i, j] : std::views::cartesian_product(
				std::views::iota(1u, input.size() - 1), std::views::iota(1u, input[0].size() - 1)))
		{
			if(input[i][j] == 0)
			{
				const auto summits = finder.searchForSummits({.x = j, .y = i});
				totalScore += summits.size();
			}
		}

		std::cout << std::format("Total score: {}\n", totalScore);
	}
	{
		Rating totalRating = 0;
		for(const auto [i, j] : std::views::cartesian_product(
				std::views::iota(1u, input.size() - 1), std::views::iota(1u, input[0].size() - 1)))
		{
			if(input[i][j] == 0)
			{
				totalRating += finder.calculateRating({.x = j, .y = i});
			}
		}

		std::cout << std::format("Total rating: {}\n", totalRating);
	}

	return 0;
}