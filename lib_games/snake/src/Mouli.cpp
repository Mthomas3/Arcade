//
// Created by styvaether on 3/27/16.
//

#include <iostream>
#include <unistd.h>
#include "../../../include/Protocol.hpp"
#include "../include/Mouli.hh"

void Mouli::loop() {
    uint16_t            c;
    arcade::CommandType command;
    std::list<arcade::Events> events;

    while (read(0, &c, sizeof(arcade::CommandType)) > 0)
    {
        command = static_cast<arcade::CommandType>(c);
        switch (command)
        {
            case arcade::CommandType::WHERE_AM_I:
                writeWhereIAm();
                break;
            case arcade::CommandType::GET_MAP:
                writeGetMap();
                break;
            case arcade::CommandType::GO_UP:
                events.push_back(arcade::Events::UP);
                break;
            case arcade::CommandType::GO_DOWN:
                events.push_back(arcade::Events::DOWN);
                break;
            case arcade::CommandType::GO_LEFT:
                events.push_back(arcade::Events::LEFT);
                break;
            case arcade::CommandType::GO_RIGHT:
                events.push_back(arcade::Events::RIGHT);
                break;
            case arcade::CommandType::GO_FORWARD:
                break;
            case arcade::CommandType::PLAY:
                _game->sendEvent(events);
                _game->update(1.0f);
                events.clear();
                break;
        }
    }
}

void Mouli::writeWhereIAm() const {
    arcade::WhereAmI *where = static_cast<arcade::WhereAmI *>(alloca(sizeof(arcade::WhereAmI) + _game->getLenght() * sizeof(arcade::Position)));

    where->type = arcade::CommandType::WHERE_AM_I;
    where->lenght = _game->getLenght();
    for (uint16_t i; i < where->lenght; i++)
        where->position[i] = _game->getPosition(i);
    write(1, where, sizeof(arcade::WhereAmI) + _game->getLenght() * sizeof(arcade::Position));
}

void Mouli::writeGetMap() const {
    arcade::GetMap  *map = static_cast<arcade::GetMap *>(alloca(sizeof(arcade::GetMap) + (30 * 40) * sizeof(arcade::TileType)));

    map->type = arcade::CommandType::GET_MAP;
    map->width = 40;
    map->height = 30;
    for (int i = 0; i < 30 * 40; i++)
        map->tile[i] = _game->getTile(i % 40, i / 40);
    write(1, map, sizeof(arcade::GetMap) + (30 * 40) * sizeof(arcade::TileType));
}