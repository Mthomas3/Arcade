//
// Created by rusign on 3/17/16.
//

#ifndef CPP_ARCADE_SNAKE_HPP
#define CPP_ARCADE_SNAKE_HPP

#include "../../../include/Modules/IGame.hh"

namespace arcade
{
    class Snake : public IGame
    {
    public :
        Snake();
        virtual ~Snake();
        virtual void init();
        virtual void closeGame();
        virtual void sendEvent(std::list<Events> &keys);
        virtual void update(float dtime);
        virtual std::vector<Entity *> getEntities();
        virtual Map *getMap();
        virtual std::string const &getName() const;

        uint16_t getLenght() const;
        Position getPosition(uint16_t index) const;
        TileType getTile(int x, int y) const;

        virtual size_t getScore() const { return _score; }

    private :
        void generatePower();
        bool isColliding();

        Entity *_power;
        Map     *_map;
        size_t  _score;
        std::string _name;
        std::vector<Entity *> _player;
        arcade::Events _dir;
        float _speed;
        float _timeElapsed;
    };
}

#endif //CPP_ARCADE_SNAKE_H