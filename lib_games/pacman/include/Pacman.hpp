//
// Created by rusign on 3/17/16.
//

#ifndef CPP_ARCADE_PACMAN_HPP
#define CPP_ARCADE_PACMAN_HPP

#include "../../../include/Modules/IGame.hh"

namespace arcade
{
    class Pacman : public IGame
    {
    public :
        Pacman();
        virtual ~Pacman();
        virtual void init();
        virtual void closeGame();
        virtual void sendEvent(std::list<Events> &keys);
        virtual void update(float dtime);
        virtual std::vector<Entity *> getEntities();
        virtual Map *getMap();
        virtual std::string const &getName() const;

        uint16_t getLenght() const;
        Position getPosition(uint16_t index) const;
        TileType getTitle(int x, int y) const;

        virtual size_t getScore() const { return _score; }

    private :
        bool isWall(int);
        bool canIMove();
        bool canIMoveDir(arcade::Events dir);
        bool canGhosMove(Entity *, arcade::Events);
        bool isGhost(int, int);
        void ghoastIa();
        void ramdom_move(Entity *);
        void generateBigP();
        void affraidGhost();
        void killGhost(int x, int y);
        void generateWall();
        void generateBorder();

        Map     *_map;
        size_t  _score;
        bool _isInCage;
        bool _wallOpen;
        float _timeCage;
        int _isMoving;
        float _affraidTime;
        bool _isGhosttAffraid;
        float _cptGhost;
        std::string _name;
        std::vector<int> _wall;
        std::vector<Entity *> _power;
        std::vector<Entity *> _powerBig;
        Entity *_player;
        Entity *_ghostR;
        Entity *_ghostB;
        Entity *_ghostP;
        Entity *_ghostO;
        arcade::Events _dir;
        arcade::Events _dirTmp;
        float _speed;
        float _timeElapsed;
    };
}

#endif //CPP_ARCADE_Pacman_H