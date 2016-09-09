//
// Created by rusign on 3/17/16.
//

#include <algorithm>
#include <iostream>
#include <iostream>
#include <fstream>
#include "../../../include/Core/Exceptions.hh"
#include "../../../include/Core/Defines.hh"
#include "../include/Pacman.hpp"

arcade::Pacman::Pacman() : _map(nullptr), _score(0), _name("Pacman"), _dir(arcade::Events::UP), _speed(0.2f), _timeElapsed(0)
{
    _isMoving = 0;
    _dirTmp = arcade::Events::UP;
    _player = nullptr;
    _ghostR = nullptr;
    _ghostB  = nullptr;
    _ghostP  = nullptr;
    _ghostO  = nullptr;
    _cptGhost = 0;
    _affraidTime = 0.0f;
    _isInCage = true;
    _timeCage = 0.0f;
    _isGhosttAffraid = false;
    srand(time(nullptr));
    _wallOpen = true;
}

arcade::Pacman::~Pacman()
{
    if (_map != nullptr)
        delete _map;
}


void arcade::Pacman::init()
{
//    if (_map)
  //      delete _map;
    _score = 0;
    _timeElapsed = 0;
    _isMoving = 0;
    _cptGhost = 0;
    _isInCage = true;
    _timeCage = 0.0f;
    _wallOpen = true;
    _player = nullptr;
    _affraidTime = 0.0f;
    _isGhosttAffraid = false;
    _dir = arcade::Events::UP;
    //if (_player)
      //  delete _player;
   /* if (_ghostR)
        delete _ghostR;
    if (_ghostB)
        delete _ghostB;
    if (_ghostP)
        delete _ghostP;
    if (_ghostO)
        delete _ghostO;
    for (size_t i = 0; i < _power.size(); i++)
        delete _power[i];*/
    _power.clear();
/*    for (size_t i = 0; i < _powerBig.size(); i++)
        delete _powerBig[i];*/
    _powerBig.clear();
    _wall.clear();
    arcade::Map *map = new arcade::Map(arcade::Pos(40, 30), arcade::Size(20, 20));
    arcade::Entity *Empty = new arcade::Entity(0x0, arcade::Pos(0, 0), nullptr, arcade::Shape(arcade::BBOX, std::make_tuple(0, 0, 0)));
    _player = new arcade::Entity(1, arcade::Pos(18, 17), nullptr,
                                                arcade::Shape(arcade::BCIRCLE, arcade::Color(255, 255, 0)));
    _ghostR = new arcade::Entity(2, arcade::Pos(18, 15), nullptr,
                                 arcade::Shape(arcade::TRIANGLE, arcade::Color(255, 0, 0)));
    _ghostB = new arcade::Entity(3, arcade::Pos(19, 15), nullptr,
                                 arcade::Shape(arcade::TRIANGLE, arcade::Color(0, 0, 255)));
    _ghostP = new arcade::Entity(4, arcade::Pos(17, 15), nullptr,
                                 arcade::Shape(arcade::TRIANGLE, arcade::Color(255, 0, 255)));
    _ghostO = new arcade::Entity(5, arcade::Pos(16, 15), nullptr,
                                 arcade::Shape(arcade::TRIANGLE, arcade::Color(150, 0, 100)));
    arcade::Entity *Wall = new arcade::Entity(6, arcade::Pos(0, 0), nullptr, arcade::Shape(arcade::BBOX, std::make_tuple(0, 0, 255)));
    generateBigP();
    generateWall();
    *map << Empty << Wall;
    for (int i = 0, j = 0; i < map->getSize(); i++) {
        if (_wall[j] == i)
        {
             *map += arcade::TileType::BLOCK;
            j++;
        }
        else
             *map += arcade::TileType::EMPTY;
    }
    _map = map;
}

void arcade::Pacman::closeGame()
{

}

void arcade::Pacman::generateBorder() {
    for (int i = 0; i < 40; i++)
        _wall.push_back(i);
    for (int i = 0; i < (40 * 30); i += 40)
        _wall.push_back(i);
    for (int i = 39; i <(40 * 30); i += 40)
        _wall.push_back(i);
    for (int i = (40 * 29); i < (40 * 30); i++)
        _wall.push_back(i);
}

void arcade::Pacman::generateWall() {
     std::ifstream file("lib_games/pacman/map/map.txt", std::ios::in);
    if(file) {
        std::string line;
        int j = 0;
        int k = 0;
        int y = -1;
        int z = 11;
        while (getline(file, line))
        {
            if (line.size() != 40)
                throw exception::ArcadeError("File: map.txt not good");
            for(int i = 0, z = 11; line[i]; i++) {
            if(line[i] != '1' && line[i] != '2' && line[i] != '0' && line[i] != '3')
                throw exception::ArcadeError("File: map.txt fail to open");
                if (k % 40 == 0)
                    y++;
                if (line[i] == '1')
                    _wall.push_back(j);
                else if (line[i] == '0') {
                    arcade::Entity *powerUp = new arcade::Entity(z++, arcade::Pos(k % 40, y), nullptr,
                                                                 arcade::Shape(arcade::SCIRCLE, arcade::Color(255, 255, 255)));
                    _power.push_back(powerUp);
                }
                j++;
                k++;
            }
        }
        if (k != 1200)
            throw exception::ArcadeError("File: map.txt not good");
        generateBorder();
        std::sort(_wall.begin(), _wall.end());
        _wall.erase(std::unique(_wall.begin(), _wall.end()), _wall.end());
        file.close();
    }
    else {
        throw exception::ArcadeError("File: map.txt fail to open");
    }
}

void arcade::Pacman::generateBigP()
{
    arcade::Entity *powerUp1 = new arcade::Entity(7, arcade::Pos(1, 1), nullptr,
                                                 arcade::Shape(arcade::BCIRCLE, arcade::Color(255, 255, 255)));
    _powerBig.push_back(powerUp1);
    arcade::Entity *powerUp2 = new arcade::Entity(8, arcade::Pos(1, 28), nullptr,
                                                 arcade::Shape(arcade::BCIRCLE, arcade::Color(255, 255, 255)));
    _powerBig.push_back(powerUp2);
    arcade::Entity *powerUp3 = new arcade::Entity(9, arcade::Pos(38, 1), nullptr,
                                                 arcade::Shape(arcade::BCIRCLE, arcade::Color(255, 255, 255)));
    _powerBig.push_back(powerUp3);
    arcade::Entity *powerUp4 = new arcade::Entity(10, arcade::Pos(38, 28), nullptr,
                                                 arcade::Shape(arcade::BCIRCLE, arcade::Color(255, 255, 255)));
    _powerBig.push_back(powerUp4);
}

void arcade::Pacman::sendEvent(std::list<Events> &keys) {
    arcade::Events tmp = _dir;
    if (std::find(keys.begin(), keys.end(), arcade::Events::RESTART_GAME) != keys.end()) {
        init();
    }
    if (std::find(keys.begin(), keys.end(), arcade::Events::UP) != keys.end()) {
        _dir = arcade::Events::UP;
        _dirTmp= arcade::Events::UP;
        if (!canIMove())
            _dir = tmp;
    }
    if (std::find(keys.begin(), keys.end(), arcade::Events::DOWN) != keys.end()) {
        _dir = arcade::Events::DOWN;
        _dirTmp= arcade::Events::DOWN;
        if (!canIMove())
            _dir = tmp;
    }
    if (std::find(keys.begin(), keys.end(), arcade::Events::LEFT) != keys.end()) {
        _dir = arcade::Events::LEFT;
        _dirTmp= arcade::Events::LEFT;
        if (!canIMove())
            _dir = tmp;
    }
    if (std::find(keys.begin(), keys.end(), arcade::Events::RIGHT) != keys.end()) {
        _dir = arcade::Events::RIGHT;
        _dirTmp= arcade::Events::RIGHT;
        if (!canIMove())
            _dir = tmp;
    }
}

bool arcade::Pacman::isWall(int pos) {

    for(int i = 0; i < _wall.size(); i++)
    {
        if (_wall[i] == pos)
            return (true);
    }
    return false;
}

bool arcade::Pacman::canIMove() {
    if (_dir == arcade::Events::UP && isWall((_player->pos.second - 1) * 40 + _player->pos.first)) {
        return false;
    }
    if (_dir == arcade::Events::DOWN && isWall((_player->pos.second + 1) * 40 + _player->pos.first)) {
        return false;
    }
    if (_dir == arcade::Events::LEFT && isWall(_player->pos.second * 40 + (_player->pos.first - 1))) {
        return false;
    }
    if (_dir == arcade::Events::RIGHT && isWall(_player->pos.second * 40 + (_player->pos.first + 1))) {
        return false;
    }
    return true;
}


bool arcade::Pacman::canIMoveDir(arcade::Events dir) {
    if (dir == arcade::Events::UP && isWall((_player->pos.second - 1) * 40 + _player->pos.first)) {
        return false;
    }
    if (dir == arcade::Events::DOWN && isWall((_player->pos.second + 1) * 40 + _player->pos.first)) {
        return false;
    }
    if (dir == arcade::Events::LEFT && isWall(_player->pos.second * 40 + (_player->pos.first - 1))) {
        return false;
    }
    if (dir == arcade::Events::RIGHT && isWall(_player->pos.second * 40 + (_player->pos.first + 1))) {
        return false;
    }
    return true;
}

void arcade::Pacman::update(float dtime)
{
    _timeElapsed += dtime;
    _cptGhost += dtime;
    if (_isInCage)
        _timeCage += dtime;
    if (_isInCage && _timeCage >= 5.0f) {
        _wall.push_back(457);
        _wall.push_back(458);
        _wall.push_back(459);
        _timeCage = 2.0f;
        _isInCage = false;
        _wallOpen = false;
    }
    if (_isGhosttAffraid)
    {
        killGhost(_player->pos.first, _player->pos.second);
        _affraidTime += dtime;
        if (_affraidTime >= 10.0f) {
            _isGhosttAffraid = false;
            _affraidTime = 0.0f;
        }
    }
    affraidGhost();
    if (canIMoveDir(_dirTmp))
        _dir = _dirTmp;
    if (_timeElapsed < _speed)
        return;
    //if (canIMove()) {
        switch (_dir) {
            case arcade::Events::UP:
                if (canIMove())
                    _player->pos.second -= 1;
                break;
            case arcade::Events::DOWN:
                if (canIMove())
                    _player->pos.second += 1;
                break;
            case arcade::Events::LEFT:
                if (canIMove())
                    _player->pos.first -= 1;
                break;
            default:
                if (canIMove())
                    _player->pos.first += 1;
                break;
        }
    //}
    for (int i = 0; i < _power.size(); i++) {
        if (_power[i]->pos.second * 40 + _power[i]->pos.first == _player->pos.second * 40 + _player->pos.first) {
            _score += 1;
         //   delete _power[i];
            _power.erase(_power.begin() + i);
            break;
        }
    }
    for (int i = 0; i < _powerBig.size(); i++) {
        if (_powerBig[i]->pos.second * 40 + _powerBig[i]->pos.first == _player->pos.second * 40 + _player->pos.first) {
            _score += 10;
           // delete _powerBig[i];
            _powerBig.erase(_powerBig.begin() + i);
            _isGhosttAffraid = true;
            break;
        }
    }

    ghoastIa();
    if (_power.size() == 0 && _powerBig.size() == 0) {
        init();
        _speed -= 0.1f;
    }
    if (!_isGhosttAffraid && isGhost(_player->pos.first, _player->pos.second)) {
        init();
    }
    _isMoving = 0;
    _timeElapsed = 0;
}

//--------------------------Ghost-----------------------
void arcade::Pacman::affraidGhost() {
 if (_isGhosttAffraid) {
     _ghostP->shape.color = std::make_tuple(0, 0, 255);
     _ghostR->shape.color = std::make_tuple(0, 0, 255);
     _ghostO->shape.color = std::make_tuple(0, 0, 255);
 }
 else {
     _ghostP->shape.color = std::make_tuple(255, 0, 255);
     _ghostR->shape.color = std::make_tuple(255, 0, 0);
     _ghostO->shape.color = std::make_tuple(150, 0, 100);
 }
}

void arcade::Pacman::killGhost(int x, int y) {
    if (_ghostR && _ghostR->pos.first == x && _ghostR->pos.second == y)
    {
        _score += 50;
        _isInCage = true;
        _ghostR->pos.first = 18;
        _ghostR->pos.second = 15;
    }
    if (_ghostB && _ghostB->pos.first == x && _ghostB->pos.second == y)
    {
        _score += 50;
        _isInCage = true;
        _ghostB->pos.first = 19;
        _ghostB->pos.second = 15;
    }
    if (_ghostP->pos.first == x && _ghostP->pos.second == y)
    {
        _score += 50;
        _isInCage = true;
        _ghostP->pos.first = 17;
        _ghostP->pos.second = 15;
    }
    if (_ghostO->pos.first == x && _ghostO->pos.second == y)
    {
        _score += 50;
        _isInCage = true;
        _ghostO->pos.first = 16;
        _ghostO->pos.second = 15;
    }
    if (_isInCage && !_wallOpen) {
        _wall.pop_back();
        _wall.pop_back();
        _wall.pop_back();
        _wallOpen = true;
    }
}

bool arcade::Pacman::isGhost(int x, int y) {
    if (_ghostR->pos.first == x && _ghostR->pos.second == y)
        return true;
    if (_ghostB->pos.first == x && _ghostB->pos.second == y)
        return true;
    if (_ghostP->pos.first == x && _ghostP->pos.second == y)
        return true;
    if (_ghostO->pos.first == x && _ghostO->pos.second == y)
        return true;
    return false;
}

bool arcade::Pacman::canGhosMove(Entity *ghost, arcade::Events dir) {
    if (dir == arcade::Events::UP && (isWall((ghost->pos.second - 1) * 40 + ghost->pos.first) || isGhost(ghost->pos.first, ghost->pos.second - 1))) {
        return false;
    }
    if (dir == arcade::Events::DOWN && (isWall((ghost->pos.second + 1) * 40 + ghost->pos.first) || isGhost(ghost->pos.first, ghost->pos.second + 1))) {
        return false;
    }
    if (dir == arcade::Events::LEFT && (isWall(ghost->pos.second * 40 + (ghost->pos.first - 1)) || isGhost(ghost->pos.first - 1, ghost->pos.second))) {
        return false;
    }
    if (dir == arcade::Events::RIGHT && (isWall(ghost->pos.second * 40 + (ghost->pos.first + 1)) || isGhost(ghost->pos.first + 1, ghost->pos.second))) {
        return false;
    }
    return true;
}

void arcade::Pacman::ramdom_move(Entity *ghost) {
    bool res = false;
    int rd = 0;
    if (_isInCage) {
         if (canGhosMove(ghost, arcade::Events::UP))
             ghost->pos.second -= 1;
         else if (canGhosMove(ghost, arcade::Events::LEFT))
             ghost->pos.first -= 1;
         else if (canGhosMove(ghost, arcade::Events::RIGHT))
             ghost->pos.first += 1;
    }
    else {
        int limit = 0;
  //      if (ghost->id == 5) {
            while (!res) {
                if (limit > 100)
                    break;
                limit++;
                rd = rand() % 4;
                switch (rd) {
                    case 0:
                        res = canGhosMove(ghost, arcade::Events::UP);
                        break;
                    case 1:
                        res = canGhosMove(ghost, arcade::Events::DOWN);
                        break;
                    case 2:
                        res = canGhosMove(ghost, arcade::Events::LEFT);
                        break;
                    case 3:
                        res = canGhosMove(ghost, arcade::Events::RIGHT);
                        break;
                }
            }
            switch (rd) {
                case 0:
                    ghost->pos.second -= 1;
                    break;
                case 1:
                    ghost->pos.second += 1;
                    break;
                case 2:
                    ghost->pos.first -= 1;
                    break;
                case 3:
                    ghost->pos.first += 1;
                    break;
            }
        }
//    }
}

void arcade::Pacman::ghoastIa() {
    if (_cptGhost > 3)
    {
        ramdom_move(_ghostR);
        ramdom_move(_ghostB);
        ramdom_move(_ghostP);
        ramdom_move(_ghostO);
    }

}

//--------------end Ghost-------------------------

std::vector<arcade::Entity *> arcade::Pacman::getEntities()
{
    std::vector<arcade::Entity *> ret;
    if (_player)
        ret.push_back(_player);

    for (size_t i = 0; i < _powerBig.size(); i++)
        ret.push_back(_powerBig[i]);
    for (size_t i = 0; i < _power.size(); i++)
        ret.push_back(_power[i]);
    if (_ghostR)
        ret.push_back(_ghostR);
    if (_ghostB)
        ret.push_back(_ghostB);
    if (_ghostP)
        ret.push_back(_ghostP);
    if (_ghostO)
        ret.push_back(_ghostO);
    return ret;
}

arcade::Map *arcade::Pacman::getMap()
{
    return _map;
}

std::string const &arcade::Pacman::getName() const
{
    return _name;
}


uint16_t arcade::Pacman::getLenght() const {
    return static_cast<uint16_t >(1);
}

arcade::Position arcade::Pacman::getPosition(uint16_t index) const {
    arcade::Position pos;

    pos.x = static_cast<uint16_t>(_player->pos.first);
    pos.y = static_cast<uint16_t>(_player->pos.second);
    return pos;
}

arcade::TileType arcade::Pacman::getTitle(int x, int y) const {
    /*if (static_cast<int>(_player->pos.first) == x && static_cast<int>(_player->pos.second) == y)
            return (arcade::TileType::OTHER);*/
    if (static_cast<int>(_ghostR->pos.first) == x && static_cast<int>(_ghostR->pos.second) == y)
            return (arcade::TileType::EVIL_DUDE);
    if (static_cast<int>(_ghostB->pos.first) == x && static_cast<int>(_ghostB->pos.second) == y)
        return (arcade::TileType::EVIL_DUDE);
    if (static_cast<int>(_ghostP->pos.first) == x && static_cast<int>(_ghostP->pos.second) == y)
        return (arcade::TileType::EVIL_DUDE);
    if (static_cast<int>(_ghostO->pos.first) == x && static_cast<int>(_ghostO->pos.second) == y)
        return (arcade::TileType::EVIL_DUDE);
    for (size_t i = 0; i < _power.size(); i++)
        if (static_cast<int>(_power[i]->pos.first) == x && static_cast<int>(_power[i]->pos.second) == y)
            return (arcade::TileType::POWERUP);
    for (size_t i = 0; i < _powerBig.size(); i++)
        if (static_cast<int>(_powerBig[i]->pos.first) == x && static_cast<int>(_powerBig[i]->pos.second) == y)
            return (arcade::TileType::POWERUP);
    for (size_t i = 0; i < _wall.size(); i++)
        if (static_cast<int>(_wall[i] % 40) == x && static_cast<int>(_wall[i] / 40) == y)
            return (arcade::TileType::BLOCK);
    return (arcade::TileType::EMPTY);
}
