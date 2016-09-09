#ifndef ARCADE_DEFINES_HH
# define ARCADE_DEFINES_HH

# include <utility>
# include <tuple>

namespace arcade
{
	typedef std::pair<unsigned int, unsigned int> Size;
	typedef std::pair<float, float> Pos;
	typedef std::tuple<char, char, char> Color;
}

#endif //ARCADE_DEFINES_HH
