#ifndef D51_HPP
#define D51_HPP
#include "day5_input.hpp"

#include <algorithm>
#include <ranges>
#include <set>
#include <span>
#include <unordered_map>

namespace d51
{

namespace views = std::views;

class RulesBook
{
	std::unordered_map<int, std::set<int>> d_rules;
	void addRule(const std::pair<int, int>& rule)
	{
		d_rules[rule.first].insert(rule.second);
	}

  public:
	explicit RulesBook(const Rules& rules)
	{
		std::ranges::for_each(rules, [this](const auto& rule) { addRule(rule); });
	}

	auto violatesRule(int first, int second) const -> bool
	{
		return d_rules.contains(second) && d_rules.at(second).contains(first);
	}
};

bool validatePagesOrder(const Pages& page, const RulesBook& rulesBook)
{
	const auto orderValidator = [&rulesBook](const auto& pages) {
		return rulesBook.violatesRule(pages.first, pages.second);
	};
	for(auto i : views::iota(0u, page.size()))
	{
		const bool isPageOrderViolatesRules = std::ranges::any_of(
			views::zip(views::repeat(page[i]), page | views::drop(i)), orderValidator);
		if(isPageOrderViolatesRules)
		{
			return false;
		}
	}
	return true;
}

uint64_t validateRequest(std::span<const Pages> requests, const RulesBook& rulesBook)
{
	uint64_t sumOfMiddleElements = 0;
	for(const auto& pages : requests)
	{
		if(validatePagesOrder(pages, rulesBook))
		{
			sumOfMiddleElements += pages[pages.size() / 2];
		}
	}
	return sumOfMiddleElements;
}
} // namespace d51
#endif