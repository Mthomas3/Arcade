//
// Created by gascon_n on 3/24/16.
//

#include "../include/Snake.hpp"
#include "../include/Mouli.hh"

extern "C" {
    arcade::IGame *getGame();
    void Play();
}

arcade::IGame *getGame()
{
    return (new arcade::Snake);
}

void Play()
{
    arcade::Snake   snake;
    Mouli           mouli(&snake);

    snake.init();
    mouli.loop();
}