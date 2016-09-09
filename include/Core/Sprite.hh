#ifndef ARCADE_SPRITE_HH
# define ARCADE_SPRITE_HH

# include <vector>
# include <string>
# include "Defines.hh"

namespace arcade
{
	struct Sprite
	{
		Sprite() { }
		Sprite(Size size) : size(size), frame(0) { }
		~Sprite() { path.clear(); }
		Sprite &operator<<(std::string const &pathName) { path.push_back(pathName); return (*this); }
		Sprite &operator++(int) { frame = ++frame % (path.size() - 1); return (*this);}

		Size size;
		size_t frame;
		std::vector<std::string> path;
	};
}

#endif //ARCADE_SPRITE_HH
