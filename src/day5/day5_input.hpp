#ifndef D5_INPUT_HPP
#define D5_INPUT_HPP
#include <charconv>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using Rules = std::vector<std::pair<int, int>>;
using Pages = std::vector<int>;
using PrintRequests = std::vector<Pages>;

std::pair<Rules, PrintRequests> parseInput(const std::filesystem::path& data)
{
	std::ifstream file(data);
	if(!file)
	{
		throw std::runtime_error("File not found");
	}

	Rules rules;
	std::string line;
	while(std::getline(file, line))
	{
		if(line.empty())
		{
			break;
		}

		int a, b = 0;
		std::from_chars_result res = std::from_chars(line.data(), line.data() + line.size(), a);
		if(*res.ptr != '|')
		{
			throw std::runtime_error("Failed to read input");
		}
		res = std::from_chars(res.ptr + 1, line.data() + line.size(), b);
		rules.push_back({a, b});
	}

	PrintRequests pages;
	while(std::getline(file, line))
	{
		Pages page;
		std::istringstream iss(line); // Stream the entire line
		int value;

		while(iss >> value)
		{ // Extract integers
			page.push_back(value);

			// Ignore the next symbol if it's a comma
			if(iss.peek() == ',')
			{
				iss.ignore(); // Skip the comma
			}
		}
		pages.emplace_back(std::move(page));
	}
	return {std::move(rules), std::move(pages)};
}

#endif