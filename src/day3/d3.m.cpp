#include <algorithm>
#include <array>
#include <charconv>
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <optional>
#include <ranges>
#include <span>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::string parseInput(std::filesystem::path path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);
	if(!file)
	{
		throw std::runtime_error(std::format("Failed to open file {}.", path.string()));
	}

	return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

std::pair<std::optional<uint32_t>, const char*> to_int(const char* start, const char* end)
{
	uint32_t result{};
	auto [ptr, ec] = std::from_chars(start, end, result);

	if(ec == std::errc::invalid_argument)
	{
		return {std::nullopt, ptr};
	}
	else if(ec == std::errc::result_out_of_range)
	{
		throw std::runtime_error("overflow");
	}

	return {result, ptr};
}

int main()
{
	auto input = parseInput("/home/vladlev/projects/AOC24/inputs/day3.txt");
	//std::string input = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";

	const std::string_view doCommand = "do()";
	const std::string_view dontCommand = "don't()";
	std::vector<std::pair<size_t, size_t>> slides;
	size_t do_from = 0;
	size_t do_until = input.find(dontCommand);
	if(do_until == std::string::npos)
	{
		do_until = input.size();
	}
	slides.emplace_back(do_from, do_until);
	while(1)
	{
		do_from = input.find(doCommand, do_until + dontCommand.size());
		if(do_from == std::string::npos)
		{
			break;
		}
		do_from += doCommand.size();
		do_until = input.find(dontCommand, do_from);
		if(do_until == std::string::npos)
		{
			do_until = input.size();
			slides.emplace_back(do_from, do_until);
			break;
		}
		slides.emplace_back(do_from, do_until);
	}

	uint64_t result = 0;
	for(auto [start, end_pos] : slides)
	{
		const char* end = input.data() + end_pos;

		while(1)
		{
			start = input.find("mul(", start);
			if(start == std::string::npos)
			{
				break;
			}
			start += 4;
			const auto [optval, nextChar] = to_int(input.data() + start, end);
			if(nextChar == end || nextChar + 1 >= end)
			{
				break;
			}

			if(!optval || *nextChar != ',')
			{
				continue;
			}

			const auto valA = *optval;
			const auto [optvalB, nextCharB] = to_int(nextChar + 1, end);
			if(nextCharB >= end)
			{
				break;
			}

			if(!optvalB || *nextCharB != ')')
			{
				continue;
			}

			const auto valB = *optvalB;
			std::cout << valA << "," << valB << std::endl;
			result += valA * valB;
		}
	}
	std::cout << result << std::endl;
	return 0;
}