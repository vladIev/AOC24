#include <algorithm>
#include <cassert>
#include <cmath>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <numeric>
#include <optional>
#include <ostream>
#include <ranges>
#include <unordered_map>
#include <vector>

using BlinkIteration = uint32_t;

using Stone = uint64_t;

std::vector<Stone> getInput(std::filesystem::path path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);
	if(!file)
	{
		throw std::runtime_error(std::format("Failed to open file {}.", path.string()));
	}

	std::vector<Stone> output;
	while(1)
	{
		Stone value = 0;
		file >> value;
		if(!file) break;
		output.emplace_back(value);
	}
	return output;
}

class RulesHelper
{

	static inline std::optional<std::pair<Stone, Stone>> trySplitValue(Stone value)
	{
		assert(value != 0);
		const auto numberOfDigits = static_cast<uint32_t>(std::log10(value)) + 1;
		if((numberOfDigits & 1) != 0) return std::nullopt;

		const uint32_t diviser = std::pow(10u, numberOfDigits / 2);
		return std::make_pair(value / diviser, value % diviser);
	}

  public:
	static inline std::pair<Stone, std::optional<uint64_t>> apply(Stone value)
	{
		if(value == 0)
		{
			return {1, {}};
		}
		else if(const auto splitedValues = trySplitValue(value); splitedValues)
		{
			const auto [val1, val2] = *splitedValues;
			return {val1, val2};
		}
		else
		{
			return {value * 2024, {}};
		}
	}
};

uint64_t solve2(const std::vector<Stone>& stones, const BlinkIteration maxIter)
{
	std::unordered_map<uint64_t, uint64_t> oldStones;
	for(const auto& stone : stones)
	{
		oldStones[stone] += 1;
	}

	for(const auto i : std::views::iota(1u, maxIter + 1))
	{

		std::unordered_map<uint64_t, uint64_t> newStones;
		for(auto [value, count] : oldStones)
		{
			const auto [left, right] = RulesHelper::apply(value);
			newStones[left] += count;
			if(right)
			{
				newStones[*right] += count;
			}
		}
		oldStones.swap(newStones);
	}

	auto values = oldStones | std::views::values;

	return std::reduce(values.cbegin(), values.cend(), 0ull);
}

int main()
{
	auto input = getInput("/home/vladlev/projects/AOC24/inputs/day11.txt");
	const BlinkIteration maxIter = 75;
	std::cout << solve2(input, maxIter) << std::endl;
	return 0;
}