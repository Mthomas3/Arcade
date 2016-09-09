#ifndef ARCADE_ENTITY_HH
# define ARCADE_ENTITY_HH

# include "Sprite.hh"
# include "Shape.hh"

namespace arcade
{

	struct Entity
	{
		Entity() { }
		Entity(size_t id, Pos pos, Sprite *sprite, Shape shape) : id(id), pos(pos), sprite(sprite), shape(shape) { }
		~Entity() { if (sprite != nullptr) delete sprite; }

		size_t id;
		Pos pos;
		float angle = 0;
		Sprite *sprite;
		Shape shape;
	};
}

#endif //ARCADE_ENTITY_HH
