//
// Created by rusig_n on 3/27/16.
//

#ifndef ARCADE_MOULI_HH
#define ARCADE_MOULI_HH

#include "Pacman.hpp"

class   Mouli
{
public:
    Mouli(arcade::Pacman *game) : _game(game) {}

    void loop();

private:
    void writeWhereIAm() const;
    void writeGetMap() const;

    arcade::Pacman *_game;
};

#endif //ARCADE_MOULI_HH
