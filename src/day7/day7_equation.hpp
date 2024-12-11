#ifndef DAY7_EQUATION_HPP
#define DAY7_EQUATION_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace ops
{
inline uint64_t plus(uint64_t a, uint64_t b)
{
	assert(std::numeric_limits<uint64_t>::max() - a >= b);
	return b + a;
}

inline uint64_t mul(uint64_t a, uint64_t b)
{
	assert(std::numeric_limits<uint64_t>::max() / a >= b);
	return b * a;
}

inline uint64_t concat(uint64_t a, uint64_t b)
{
	std::string result_str = std::to_string(b) + std::to_string(a);
	std::stringstream ss(result_str);
	uint64_t result;
	ss >> result;
	return result;
}
} // namespace ops

struct Equation
{
	using OperationT = std::function<uint64_t(uint64_t, uint64_t)>;

	uint64_t response;
	std::vector<uint64_t> args;

  private:
	bool isSolvalable(size_t ind, uint64_t total, OperationT operation) const
	{
		if(ind >= args.size())
		{
			return total == response;
		}
		const auto result = operation(args[ind], total);
		return isSolvalable(ind + 1, result, ops::plus) ||
			   isSolvalable(ind + 1, result, ops::mul) ||
			   isSolvalable(ind + 1, result, ops::concat);
	}

  public:
	Equation() = default;
	Equation(const std::string& line)
	{
		char sep = 0;
		std::stringstream ss(line);
		ss >> response;
		ss >> sep;
		assert(sep == ':');
		std::copy(std::istream_iterator<uint32_t>(ss),
				  std::istream_iterator<uint32_t>(),
				  std::back_inserter(args));
	}

	bool isSolvalable() const
	{
		return isSolvalable(1, args[0], ops::plus) || isSolvalable(1, args[0], ops::mul) ||
			   isSolvalable(1, args[0], ops::concat);
	}
};

#endif