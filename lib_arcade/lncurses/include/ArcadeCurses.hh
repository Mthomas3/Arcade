//
// Created by mart_4 on 3/22/16.
//

#ifndef ARCADE_ARCADECURSES_H
#define ARCADE_ARCADECURSES_H

#include <ncurses.h>
#include <iostream>
#include <Modules/IOInterface.hh>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../sfml/include/ShapeFactory.hh"

# define F1 265
# define F2 266
# define F3 267
# define F4 268
# define F5 269
# define F6 270
# define F7 271
# define F8 272
# define F9 273
# define F10 274

namespace Graphic
{
    class ArcadeCurses : public arcade::IOInterface
    {

    public :
        ArcadeCurses(void);
        virtual ~ArcadeCurses(void){};
        virtual void init(void);
        virtual void display(void);
        virtual void createWindow(size_t x, size_t y);
        virtual void destroyWindow();
        virtual void setEntities(const std::vector<arcade::Entity *> &entities);
        virtual std::list<arcade::Events> getEvents();
        virtual void sendMap(arcade::Map *map);
        virtual void sendScore(size_t score);

    private :

        int                                 _key;
        size_t                              _score;
        WINDOW                              *_wind;
        arcade::Map                         *_map;
        std::vector<arcade::Entity *>       _entities;
        std::vector<arcade::Entity *>       _mapEntities;
        void printTriangle(int startrow, int startcol, int height);
        void printToScreen(int pos_x, int pos_y, const char carac) const;
        void printRectangle(int startrow, int startcol, int height, int width);
        void colorOff(int pair);
        void colorOn(int pair);

        short convertColor(arcade::Color color);

        void printScore();
    };

}

#endif //ARCADE_ARCADECURSES_H
