#ifndef D4_HPP
#define D4_HPP

#include <array>
#include <cstdint>

template <uint32_t COLS, uint32_t ROWS>
using Input = std::array<std::array<char, COLS>, ROWS>;

template <typename Underlying>
struct Coord
{
	Underlying x, y;
};
using Direction = Coord<int>;
using Position = Coord<uint32_t>;

template <uint32_t COLS, uint32_t ROWS>
auto makeExtendendInput(const Input<COLS, ROWS>& input)
{
	constexpr uint32_t EXTENDEND_COLS = COLS + 2;
	constexpr uint32_t EXTENDEND_ROWS = ROWS + 2;
	Input<EXTENDEND_COLS, EXTENDEND_ROWS> output;
	for(auto& el : output[0])
	{
		el = '|';
	}
	for(auto i = 0; i < input.size(); i++)
	{
		output[i + 1][0] = '|';
		std::copy(input[i].cbegin(), input[i].cend(), std::begin(output[i + 1]) + 1);
		output[i + 1][EXTENDEND_COLS - 1] = '|';
	}
	for(auto& el : output[EXTENDEND_ROWS - 1])
	{
		el = '|';
	}
	return output;
}

inline char nextXmasChar(char currentChar)
{
	switch(currentChar)
	{
	case 'X':
		return 'M';
	case 'M':
		return 'A';
	case 'A':
		return 'S';
	default:
		return '\0';
	}
}

template <uint32_t COLS, uint32_t ROWS>
bool analyzeDirection(const Input<COLS, ROWS>& extInput,
					  const Position& startPos,
					  const Direction& direction)
{
	auto current_x = startPos.x;
	auto current_y = startPos.y;
	auto expectedChar = nextXmasChar('X');
	while(expectedChar != '\0')
	{
		auto next_x = current_x + direction.x;
		auto next_y = current_y + direction.y;
		if(expectedChar != extInput[next_y][next_x])
		{
			return false;
		}
		current_x = next_x;
		current_y = next_y;
		expectedChar = nextXmasChar(expectedChar);
	}
	return true;
}

template <uint32_t COLS, uint32_t ROWS>
uint32_t cntrXmasForCell(const Input<COLS, ROWS>& extInput, Position startPos)
{
	constexpr std::array<Direction, 8> directions{
		Direction{-1, -1},
		Direction{0, -1},
		Direction{1, -1},
		Direction{-1, 0},
		Direction{1, 0},
		Direction{-1, 1},
		Direction{0, 1},
		Direction{1, 1},
	};

	uint32_t cntr = 0;
	for(const auto& direction : directions)
	{
		cntr += analyzeDirection<COLS, ROWS>(extInput, startPos, direction);
	}

	return cntr;
}

template <uint32_t COLS, uint32_t ROWS>
uint32_t countXmas(const Input<COLS, ROWS>& extInput)
{
	uint32_t xmasCntr = 0;
	for(uint32_t i = 1; i <= extInput.size() - 1; i++)
	{
		for(uint32_t j = 1; j <= extInput[0].size() - 1; j++)
		{
			if(extInput[i][j] == 'X')
			{
				Position startingPos{j, i};
				xmasCntr += cntrXmasForCell<COLS, ROWS>(extInput, startingPos);
			}
		}
	}
	return xmasCntr;
}

#endif