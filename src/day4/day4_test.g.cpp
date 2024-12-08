#include "day4.hpp"
#include "day42.hpp"

#include <array>
#include <gtest/gtest.h>

TEST(TEST, cntrXmasForCell)
{
	const std::array<std::array<char, 7>, 7> data{
		std::to_array({'S', 'O', 'O', 'S', 'O', 'O', 'S'}),
		std::to_array({'O', 'A', 'O', 'A', 'O', 'A', 'O'}),
		std::to_array({'O', 'O', 'M', 'M', 'M', 'O', 'O'}),
		std::to_array({'S', 'A', 'M', 'X', 'M', 'A', 'S'}),
		std::to_array({'O', 'O', 'M', 'M', 'M', 'O', 'O'}),
		std::to_array({'O', 'A', 'O', 'A', 'O', 'A', 'O'}),
		std::to_array({'S', 'O', 'O', 'S', 'O', 'O', 'S'}),
	};

	auto extData = makeExtendendInput<7, 7>(data);
	auto cntr = cntrXmasForCell<9, 9>(extData, Position{4, 4});
	EXPECT_EQ(8u, cntr);
}

TEST(TEST, d42)
{
	const std::array<std::array<char, 10>, 10> data{
		std::to_array({
			'M',
			'M',
			'M',
			'S',
			'X',
			'X',
			'M',
			'A',
			'S',
			'M',
		}),
		std::to_array({
			'M',
			'S',
			'A',
			'M',
			'X',
			'M',
			'S',
			'M',
			'S',
			'A',
		}),
		std::to_array({
			'A',
			'M',
			'X',
			'S',
			'X',
			'M',
			'A',
			'A',
			'M',
			'M',
		}),
		std::to_array({
			'M',
			'S',
			'A',
			'M',
			'A',
			'S',
			'M',
			'S',
			'M',
			'X',
		}),
		std::to_array({
			'X',
			'M',
			'A',
			'S',
			'A',
			'M',
			'X',
			'A',
			'M',
			'M',
		}),
		std::to_array({
			'X',
			'X',
			'A',
			'M',
			'M',
			'X',
			'X',
			'A',
			'M',
			'A',
		}),
		std::to_array({
			'S',
			'M',
			'S',
			'M',
			'S',
			'A',
			'S',
			'X',
			'S',
			'S',
		}),
		std::to_array({
			'S',
			'A',
			'X',
			'A',
			'M',
			'A',
			'S',
			'A',
			'A',
			'A',
		}),
		std::to_array({
			'M',
			'A',
			'M',
			'M',
			'M',
			'X',
			'M',
			'M',
			'M',
			'M',
		}),
		std::to_array({
			'M',
			'X',
			'M',
			'X',
			'A',
			'X',
			'M',
			'A',
			'S',
			'X',
		}),
	};

	auto extData = makeExtendendInput<10, 10>(data);
	auto cntr = countX_mas<12, 12>(extData);
	EXPECT_EQ(9u, cntr);
}

TEST(TEST, countXmas)
{
	const std::array<std::array<char, 7>, 9> data{
		std::to_array({'S', 'A', 'M', 'X', 'M', 'A', 'S'}),
		std::to_array({'S', 'O', 'O', 'S', 'O', 'O', 'S'}),
		std::to_array({'O', 'A', 'O', 'A', 'O', 'A', 'O'}),
		std::to_array({'O', 'O', 'M', 'M', 'M', 'O', 'O'}),
		std::to_array({'S', 'A', 'M', 'X', 'M', 'A', 'S'}),
		std::to_array({'O', 'O', 'M', 'M', 'M', 'O', 'O'}),
		std::to_array({'O', 'A', 'O', 'A', 'O', 'A', 'O'}),
		std::to_array({'S', 'O', 'O', 'S', 'O', 'O', 'S'}),
		std::to_array({'X', 'M', 'A', 'S', 'A', 'M', 'X'}),

	};

	auto extData = makeExtendendInput<7, 9>(data);
	auto cntr = countXmas<9, 11>(extData);
	EXPECT_EQ(12u, cntr);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}