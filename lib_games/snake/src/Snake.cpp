//
// Created by rusign on 3/17/16.
//

#include <algorithm>
#include <iostream>
#include "../../../include/Core/Defines.hh"
#include "../include/Snake.hpp"

arcade::Snake::Snake() : _power(nullptr), _map(nullptr), _score(0), _name("Snake"), _dir(arcade::Events::RIGHT), _speed(0.4f), _timeElapsed(0)
{
}

arcade::Snake::~Snake()
{
     if (_map != nullptr)
        delete _map;
}

void arcade::Snake::init()
{
    _score = 0;
    _dir = arcade::Events::RIGHT;
    _timeElapsed = 0;
    _player.clear();
    arcade::Map *map = new arcade::Map(arcade::Pos(40, 30), arcade::Size(20, 20));
    arcade::Entity *Empty = new arcade::Entity(0x0, arcade::Pos(0, 0), nullptr, arcade::Shape(arcade::BBOX, std::make_tuple(255, 255, 255)));
    for (size_t i = 0; i < 4; i++)
    {
        arcade::Entity *player = new arcade::Entity(i + 1, arcade::Pos(20 - i, 15), nullptr,
                                                    arcade::Shape(arcade::BBOX, arcade::Color(0, 0, 0)));
        _player.push_back(player);
    }
    *map << Empty;
    for (int i = 0; i < map->getSize(); i++)
        *map += arcade::TileType::EMPTY;
    _map = map;
    generatePower();
}

void arcade::Snake::closeGame()
{

}

void arcade::Snake::sendEvent(std::list<Events> &keys)
{
    if (std::find(keys.begin(), keys.end(), arcade::Events::RESTART_GAME) != keys.end()) {
        init();
    }
    if (std::find(keys.begin(), keys.end(), arcade::Events::UP) != keys.end() && _dir != arcade::Events::DOWN)
        _dir = arcade::Events::UP;
    if (std::find(keys.begin(), keys.end(), arcade::Events::DOWN) != keys.end() && _dir != arcade::Events::UP)
        _dir = arcade::Events::DOWN;
    if (std::find(keys.begin(), keys.end(), arcade::Events::LEFT) != keys.end() && _dir != arcade::Events::RIGHT)
        _dir = arcade::Events::LEFT;
    if (std::find(keys.begin(), keys.end(), arcade::Events::RIGHT) != keys.end() && _dir != arcade::Events::LEFT)
        _dir = arcade::Events::RIGHT;
}

void arcade::Snake::update(float dtime)
{
    _timeElapsed += dtime;
    if (_timeElapsed < 0.07f)
        return;
    if (_player.size() < 1)
        return;
    int x = static_cast<int>(_player[_player.size() - 1]->pos.first);
    int y = static_cast<int>(_player[_player.size() - 1]->pos.second);
    for (size_t i = _player.size() - 1; i > 0; i--)
    {
        _player[i]->shape.color = std::make_tuple(0, 0, 0);
        _player[i]->pos.first = _player[i - 1]->pos.first;
        _player[i]->pos.second = _player[i - 1]->pos.second;
    }
    if ((_dir == arcade::Events::UP && _player[0]->pos.second == 0) ||
                (_dir == arcade::Events::DOWN && _player[0]->pos.second == _map->getLength() - 1) ||
                (_dir == arcade::Events::RIGHT && _player[0]->pos.first == _map->getWidth() - 1) ||
                (_dir == arcade::Events::LEFT && _player[0]->pos.first == 0))
    {
        init();
        return;
    }
    switch (_dir)
    {
        case arcade::Events::UP:
            _player[0]->pos.second -= 1;
            break;
        case arcade::Events::DOWN:
            _player[0]->pos.second += 1;
            break;
        case arcade::Events::LEFT:
            _player[0]->pos.first -= 1;
            break;
        default:
            _player[0]->pos.first += 1;
            break;
    }
    if (isColliding()) {
        init();
        return;
    }
    if (_player[0]->pos.first == _power->pos.first && _player[0]->pos.second == _power->pos.second)
    {
        _score += 10;
        // delete _power;
        _power = nullptr;
        arcade::Entity *pl = new arcade::Entity(_player.size(), arcade::Pos(x, y), nullptr,
                                                arcade::Shape(arcade::BBOX, arcade::Color(0, 0, 0)));
        _player.push_back(pl);
        generatePower();
    }
    _timeElapsed = 0;
}

std::vector<arcade::Entity *> arcade::Snake::getEntities()
{
    std::vector<arcade::Entity *> ret;

    if (_power)
        ret.push_back(_power);
    for (size_t i = 0; i < _player.size(); i++)
        ret.push_back(_player[i]);
    return ret;
}

arcade::Map *arcade::Snake::getMap()
{
    return _map;
}

std::string const &arcade::Snake::getName() const
{
    return _name;
}

void arcade::Snake::generatePower()
{
    int x = rand() % _map->getWidth();
    int y = rand() % _map->getLength();

    for (int i = 0; i < _player.size(); i++)
        if (_player[i]->pos.first == x && _player[i]->pos.second == y)
        {
            x = rand() % _map->getWidth();
            y = rand() % _map->getLength();
            i = -1;
        }
    _power = new arcade::Entity(0, arcade::Pos(x, y), nullptr,
                                                arcade::Shape(arcade::BBOX, arcade::Color(255, 0, 0)));
}

bool arcade::Snake::isColliding()
{
    for (size_t i = 0; i < _player.size(); i++)
        for (size_t j = 0; j < _player.size(); j++)
            if (i != j && _player[i]->pos.first == _player[j]->pos.first && _player[i]->pos.second == _player[j]->pos.second)
                return true;
    return false;
}

uint16_t arcade::Snake::getLenght() const {
    return static_cast<uint16_t >(_player.size());
}

arcade::Position arcade::Snake::getPosition(uint16_t index) const {
    arcade::Position pos;

    pos.x = static_cast<uint16_t>(_player[index]->pos.first);
    pos.y = static_cast<uint16_t>(_player[index]->pos.second);
    return pos;
}

arcade::TileType arcade::Snake::getTile(int x, int y) const {
    if (_power)
        if (static_cast<int>(_power->pos.first) == x && static_cast<int>(_power->pos.second) == y)
            return (arcade::TileType::POWERUP);
    /*for (size_t i = 0; i < _player.size(); i++)
        if (static_cast<int>(_player[i]->pos.first) == x && static_cast<int>(_player[i]->pos.second) == y)
            return (arcade::TileType::OTHER);*/
    return (arcade::TileType::EMPTY);
}

