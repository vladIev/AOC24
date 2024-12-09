#include "day6_1.hpp"
#include "day6_2.hpp"
#include "day6_input.hpp"

#include <gtest/gtest.h>

TEST(day6, leavemap1)
{
	const std::string map = R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...
)";

	auto [ox, oy, sp] = parseMap(map);
	EXPECT_TRUE(canLeaveMap(ox, oy, sp));
}

TEST(day6, leavemap2)
{
	const std::string map = R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#.#^.....
........#.
#.........
......#...
)";

	auto [ox, oy, sp] = parseMap(map);
	EXPECT_FALSE(canLeaveMap(ox, oy, sp));
}

TEST(day6, leavemap3)
{
	const std::string map = R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
......#.#.
#.........
......#...
)";

	auto [ox, oy, sp] = parseMap(map);
	EXPECT_FALSE(canLeaveMap(ox, oy, sp));
}

TEST(day6, leavemap4)
{
	const std::string map = R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
.......##.
#.........
......#...
)";

	auto [ox, oy, sp] = parseMap(map);
	EXPECT_FALSE(canLeaveMap(ox, oy, sp));
}

TEST(day6, leavemap5)
{
	const std::string map = R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
##........
......#...
)";

	auto [ox, oy, sp] = parseMap(map);
	EXPECT_FALSE(canLeaveMap(ox, oy, sp));
}

TEST(day6, leavemap6)
{
	const std::string map = R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#..#......
......#...
)";

	auto [ox, oy, sp] = parseMap(map);
	EXPECT_FALSE(canLeaveMap(ox, oy, sp));
}

TEST(day6, leavemap7)
{
	const std::string map = R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......##..
)";

	auto [ox, oy, sp] = parseMap(map);
	EXPECT_FALSE(canLeaveMap(ox, oy, sp));
}

TEST(day6, leavemap8)
{
	const std::string map = R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...
)";

	auto [ox, oy, sp] = parseMap(map);
	std::unordered_set<Position, PositionHash> passed(10, PositionHash(10));
	passed.insert(Position{2, 7});
	//EXPECT_TRUE(canLeaveMap(ox, oy, sp));
	EXPECT_EQ(0, countPossibleLoops(passed, ox, oy, sp));
}

TEST(day6, leavemap9)
{
	const std::string map = R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
..#.....#.
#.........
......#...
)";

	auto [ox, oy, sp] = parseMap(map);
	EXPECT_TRUE(canLeaveMap(ox, oy, sp));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}