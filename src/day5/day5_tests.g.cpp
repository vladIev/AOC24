#include "day5_1.hpp"
#include "day5_2.hpp"
#include "day5_input.hpp"

#include <gtest/gtest.h>

const Rules rules{
	{47, 53}, {97, 13}, {97, 61}, {97, 47}, {75, 29}, {61, 13}, {75, 53},
	{29, 13}, {97, 29}, {53, 29}, {61, 53}, {97, 53}, {61, 29}, {47, 13},
	{75, 47}, {97, 75}, {47, 61}, {75, 61}, {47, 29}, {75, 13}, {53, 13},
};
const d51::RulesBook book(rules);
const PrintRequests requests{
	Pages{75, 47, 61, 53, 29},
	Pages{97, 61, 53, 29, 13},
	Pages{75, 29, 13},
	Pages{75, 97, 47, 61, 53},
	Pages{61, 13, 29},
	Pages{97, 13, 75, 29, 47},
};

const std::vector<bool> results{true, true, true, false, false, false};

const PrintRequests correctedRequests{
	Pages{75, 47, 61, 53, 29},
	Pages{97, 61, 53, 29, 13},
	Pages{75, 29, 13},
	Pages{97, 75, 47, 61, 53},
	Pages{61, 29, 13},
	Pages{97, 75, 47, 29, 13},
};

TEST(day5, validatePagesOrder)
{
	for(const auto& [pages, expected_result] : std::views::zip(requests, results))
	{
		EXPECT_EQ(d51::validatePagesOrder(pages, book), expected_result);
	}
}

TEST(day5, validateRequests)
{
	EXPECT_EQ(d51::validateRequest(requests, book), 143);
}

TEST(day5, fixOrder)
{
	auto copy = requests;
	for(std::tuple<Pages&, const Pages&> el : std::views::zip(copy, correctedRequests))
	{
		Pages& reqest = std::get<0>(el);
		const Pages& corrected = std::get<1>(el);
		d52::fixOrder(reqest, book);
		EXPECT_EQ(reqest, corrected);
	}
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}