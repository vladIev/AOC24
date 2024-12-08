#include "day5_1.hpp"
#include "day5_input.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <ranges>

using namespace d51;
namespace d52
{

PrintRequests getInvalidRequests(std::span<const Pages> requests, const RulesBook& rulesBook)
{
	PrintRequests invalidRequests;
	invalidRequests.reserve(requests.size());
	std::ranges::copy_if(
		requests, std::back_inserter(invalidRequests), [&rulesBook](const auto& request) {
			return !d51::validatePagesOrder(request, rulesBook);
		});
	return invalidRequests;
}

void fixOrder(Pages& pages, const RulesBook& rulesBook)
{
	const auto original = pages;
	for(auto i = 0u; i < pages.size(); i++)
	{
		for(auto j = i + 1; j < pages.size(); j++)
		{
			const auto first = pages[i];
			const auto second = pages[j];
			if(rulesBook.violatesRule(first, second))
			{
				std::swap(pages[i], pages[j]);
				j = i + 1;
			}
		}
	}

	if(!validatePagesOrder(pages, rulesBook))
	{

		std::cout << "\n\nFailed to fix order. \nOriginal: ";
		std::ranges::copy(original, std::ostream_iterator<int>(std::cout, ", "));
		std::cout << "\nResult:   ";
		std::ranges::copy(pages, std::ostream_iterator<int>(std::cout, ", "));
	}
}

uint64_t solve(std::span<const Pages> requests, const RulesBook& rulesBook)
{
	uint64_t sumOfMiddleElements = 0;
	PrintRequests invalidRequests = getInvalidRequests(requests, rulesBook);
	for(auto& pages : invalidRequests)
	{
		fixOrder(pages, rulesBook);
		sumOfMiddleElements += pages[pages.size() / 2];
	}
	return sumOfMiddleElements;
}

} // namespace d52