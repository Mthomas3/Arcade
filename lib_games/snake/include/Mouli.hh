//
// Created by styvaether on 3/27/16.
//

#ifndef ARCADE_MOULI_HH
#define ARCADE_MOULI_HH

#include "Snake.hpp"

class   Mouli
{
public:
    Mouli(arcade::Snake *game) : _game(game) {}

    void loop();

private:
    void writeWhereIAm() const;
    void writeGetMap() const;

    arcade::Snake *_game;
};

#endif //ARCADE_MOULI_HH
