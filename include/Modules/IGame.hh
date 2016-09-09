#ifndef ARCADE_IGAME_HH
# define ARCADE_IGAME_HH

# include <list>
# include <vector>
# include "../Core/Enums.hh"
# include "../Core/Entity.hh"
# include "../Core/Map.hh"

namespace arcade
{
	class IGame
	{
	public:
		virtual void init() = 0;
		virtual void closeGame() = 0;
		virtual void sendEvent(std::list<Events> &keys) = 0;
		virtual void update(float dtime) = 0;
		virtual std::vector<Entity *> getEntities() = 0;
		virtual Map *getMap() = 0;
		virtual std::string const &getName() const = 0;
		virtual size_t getScore() const = 0;
	};
}

extern "C" {
void Play();
}

#endif //ARCADE_IGAME_HH
