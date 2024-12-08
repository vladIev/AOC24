#include "day4.hpp"
#include <array>
#include <cstdint>
#include <unordered_map>

template <uint32_t COLS, uint32_t ROWS>
bool validateX_masCell(const Input<COLS, ROWS>& extInput, Position startPos)
{
	constexpr std::array<Direction, 8> directions{
		Direction{-1, -1},
		Direction{1, -1},
		Direction{-1, 1},
		Direction{1, 1},
	};

	std::unordered_map<char, int8_t> cntrs{{'M', 0}, {'S', 0}};
	for(const auto& dir : directions)
	{
		auto letter = extInput[startPos.y + dir.y][startPos.x + dir.x];
		cntrs[letter] += 1;
	}

	return cntrs['M'] == 2 && cntrs['S'] == 2 &&
		   extInput[startPos.y - 1][startPos.x - 1] != extInput[startPos.y + 1][startPos.x + 1];
}

template <uint32_t COLS, uint32_t ROWS>
uint32_t countX_mas(const Input<COLS, ROWS>& extInput)
{
	uint32_t xmasCntr = 0;
	for(uint32_t i = 1; i <= extInput.size() - 1; i++)
	{
		for(uint32_t j = 1; j <= extInput[0].size() - 1; j++)
		{
			if(extInput[i][j] == 'A')
			{
				Position startingPos{j, i};
				xmasCntr += validateX_masCell<COLS, ROWS>(extInput, startingPos);
			}
		}
	}
	return xmasCntr;
}