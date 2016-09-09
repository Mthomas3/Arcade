#ifndef ARCADE_IOINTERFACE_HH
# define ARCADE_IOINTERFACE_HH

# include <list>
# include <vector>
# include "../Protocol.hpp"
# include "../Core/Enums.hh"
# include "../Core/Entity.hh"
# include "../Core/Map.hh"

namespace arcade
{
        class IOInterface
        {
        public:
                virtual void init() = 0;
                virtual void display() = 0;
                virtual void createWindow(size_t x, size_t y) = 0;
                virtual void destroyWindow() = 0;
                virtual void setEntities(const std::vector<Entity *> &entities) = 0;
                virtual std::list<Events> getEvents() = 0;
                virtual void sendMap(Map *map) = 0;
                virtual void sendScore(size_t score) = 0;
        };
}

#endif //ARCADE_IOINTERFACE_HH