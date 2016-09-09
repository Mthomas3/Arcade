#ifndef ARCADE_SHAPE_HH
# define ARCADE_SHAPE_HH

# include "Defines.hh"
# include "Enums.hh"

namespace arcade
{
	struct Shape
	{
		Shape() { }
		Shape(Type type, Color color) : type(type), color(color) { }

		Type type;
		Color color;
	};
}

#endif //ARCADE_SHAPE_HH
