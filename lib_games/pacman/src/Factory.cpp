//
// Created by rusig_n on 3/24/16.
//

#include "../include/Pacman.hpp"
#include "../include/Mouli.hh"

extern "C" {
    arcade::IGame *getGame();
    void Play();
}

arcade::IGame *getGame()
{
    return (new arcade::Pacman);
}

void Play()
{
    arcade::Pacman   Pacman;
    Mouli           mouli(&Pacman);

    Pacman.init();
    mouli.loop();
}