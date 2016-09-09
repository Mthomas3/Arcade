//
// Created by mart_4 on 3/22/16.
//

#include <unistd.h>
#include <Core/Exceptions.hh>
#include <sstream>
#include "../include/ArcadeCurses.hh"

extern "C" {
    arcade::IOInterface *getGraphic();
}

arcade::IOInterface *getGraphic()
{
    return (new Graphic::ArcadeCurses);
}

Graphic::ArcadeCurses::ArcadeCurses(void) {
  this->_map = nullptr;
  this->_wind = new WINDOW;
}

void Graphic::ArcadeCurses::colorOn(int pair)
{
  if ((attron(COLOR_PAIR(pair))) == ERR)
    throw exception::GraphicError("attron has failed");
}

void Graphic::ArcadeCurses::colorOff(int pair)
{
  if ((attroff(COLOR_PAIR(pair))) == ERR)
    throw exception::GraphicError("attroff has failed");
}

void Graphic::ArcadeCurses::init(void)
{
  if (!(this->_wind = initscr()))
    throw exception::GraphicError("initscr has failed");
  else if ((curs_set(false)) == ERR)
    throw exception::GraphicError("curs_set has failed");
  else if ((start_color()) == ERR)
    throw exception::GraphicError("start_color has failed");
  else if ((nodelay(this->_wind, TRUE)) == ERR)
    throw exception::GraphicError("nodelay has failed");
  else if ((keypad(this->_wind, TRUE)) == ERR)
    throw exception::GraphicError("keypad has failed");
  else if ((init_pair(1, COLOR_BLACK, COLOR_BLACK)) == ERR)
    throw exception::GraphicError("cannot init color black");
  else if ((init_pair(2, COLOR_RED, COLOR_RED)) == ERR)
    throw exception::GraphicError("cannot init color red");
  else if ((init_pair(3, COLOR_GREEN, COLOR_GREEN)) == ERR)
    throw exception::GraphicError("cannot init color green");
  else if ((init_pair(4, COLOR_YELLOW, COLOR_YELLOW)) == ERR)
    throw exception::GraphicError("cannot init color yellow");
  else if ((init_pair(5, COLOR_BLUE, COLOR_BLUE)) == ERR)
    throw exception::GraphicError("cannot init blue color");
  else if ((init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA)) == ERR)
    throw exception::GraphicError("cannot init magenta color");
  else if ((init_pair(7, COLOR_CYAN, COLOR_CYAN)) == ERR)
    throw exception::GraphicError("cannot init cyan color");
  else if ((init_pair(8, COLOR_WHITE, COLOR_WHITE)) == ERR)
    throw exception::GraphicError("cannot init white color");
  else if ((noecho()) == ERR)
    throw exception::GraphicError("noecho has failed");
}

short Graphic::ArcadeCurses::convertColor(arcade::Color color)
{
        short colorKey[8] = {COLOR_BLACK,
                             COLOR_RED,
                             COLOR_GREEN,
                             COLOR_YELLOW,
                             COLOR_BLUE,
                             COLOR_MAGENTA,
                             COLOR_CYAN,
                             COLOR_WHITE};
        short colorFlags[8] = {0x000, 0x100, 0x010,
                               0x110, 0x001, 0x101,
                               0x011, 0x111};

  short colorValue = 0x000;
        short colorFinalValue = COLOR_WHITE;

        colorValue |= (static_cast<uint8_t>(std::get<0>(color)) > 255 / 2) ? 0x100 : 0;
        colorValue |= (static_cast<uint8_t>(std::get<1>(color)) > 255 / 2) ? 0x010 : 0;
        colorValue |= (static_cast<uint8_t>(std::get<2>(color)) > 255 / 2) ? 0x001 : 0;

        for (int i = 0; i < 8; i++) {
          if (colorValue == colorFlags[i]) {
            colorFinalValue = colorKey[i];
          }
        }
  return (colorFinalValue);
}

void Graphic::ArcadeCurses::setEntities(const std::vector<arcade::Entity *> &entities)
{
  this->_entities.clear();

  for (arcade::Entity *entity : entities)
  {
    _entities.push_back(entity);
  }
}

void Graphic::ArcadeCurses::printScore(void) {
  size_t number = _score;
  std::string result;
  std::ostringstream convert;

  convert << number;
  result = convert.str();
  if ((move(_map->getLength(), 0)) == ERR)
    throw exception::GraphicError("move has failed");
  else if ((clrtoeol()) == ERR)
    throw exception::GraphicError("clrtoeol has failed");
  mvwprintw(this->_wind, (_map->getLength()), 10, "Score : ");
  mvwprintw(this->_wind, (_map->getLength()), 20, result.c_str());
}

void Graphic::ArcadeCurses::display(void)
{
  if (_map == nullptr)
    return;
  for (int i = 0; i < this->_mapEntities.size(); ++i)
  {
    short fcolor = convertColor(_mapEntities[i]->shape.color);
    if ((attron(COLOR_PAIR(fcolor + 1))) == ERR)
      throw exception::GraphicError("attron has failed");
    switch (_mapEntities[i]->shape.type)
    {

      case arcade::Type::SBOX:
            printRectangle((i / _map->getWidth()), (i % _map->getWidth()), 0.1, 0.1);
            break;
      case arcade::Type::BBOX:
            printRectangle((i / _map->getWidth()), (i % _map->getWidth()), 0.5, 0.5);
            break;
      case arcade::Type::SCIRCLE:
           printRectangle((i / _map->getWidth()), (i % _map->getWidth()), 1, 1);
            break;
      case arcade::Type::BCIRCLE:
            printRectangle((i / _map->getWidth()), (i % _map->getWidth()), 1, 1);
            break;
      case arcade::Type::TRIANGLE:
            printRectangle((i / _map->getWidth()), (i % _map->getWidth()), 1, 1);
            break;
      }
    if ((attroff(COLOR_PAIR(fcolor + 1))) == ERR)
      throw exception::GraphicError("attroff has failed");
  }
  for (int i = 0; i < this->_entities.size(); ++i)
  {
    short fcolor = convertColor(_entities[i]->shape.color);
    if ((attron(COLOR_PAIR(fcolor + 1))) == ERR)
      throw exception::GraphicError("attron has failed");
    switch (_entities[i]->shape.type)
    {
      case arcade::Type::SCIRCLE: {
        if ((attroff(COLOR_PAIR(fcolor + 1))) == ERR)
          throw exception::GraphicError("attrof has failed");
        printToScreen(static_cast<int>(_entities[i]->pos.second), static_cast<int>(_entities[i]->pos.first), '*');
        break;
      }
        case arcade::Type::SBOX:
            printRectangle(static_cast<int>(_entities[i]->pos.second), static_cast<int>(_entities[i]->pos.first), 0.1, 0.1);
        break;
      case arcade::Type::BBOX: {
        printRectangle(static_cast<int>(_entities[i]->pos.second), static_cast<int>(_entities[i]->pos.first), 0.5, 0.5);
        break;
      }
        case arcade::Type::BCIRCLE:
          //printToScreen(static_cast<int>(_entities[i]->pos.second), static_cast<int>(_entities[i]->pos.first), 'O');
          printRectangle(static_cast<int>(_entities[i]->pos.second), static_cast<int>(_entities[i]->pos.first), 0.5, 0.5);
        break;
      case arcade::Type::TRIANGLE:
            printRectangle(static_cast<int>(_entities[i]->pos.second), static_cast<int>(_entities[i]->pos.first), 0.5, 0.5);
        break;
      }
    if ((attroff(COLOR_PAIR(fcolor + 1))) == ERR)
      throw exception::GraphicError("attrof has failed");
  }
  printScore();
}

void  Graphic::ArcadeCurses::createWindow(size_t x, size_t y)
{
  if ((wresize(this->_wind, x, y)) == ERR)
    throw exception::GraphicError("wresize has failed");
}
void Graphic::ArcadeCurses::destroyWindow(void)
{
  erase();
  if ((endwin()) == ERR)
    throw exception::GraphicError("endwin has failed");
}

std::list<arcade::Events > Graphic::ArcadeCurses::getEvents(void)
{
  std::list<arcade::Events> events;

  _key = getch();
  switch(_key) {
  case 27:
    events.push_back(arcade::Events::CLOSE);
    break;
  case KEY_UP:
    events.push_back(arcade::Events::UP);
    break;
  case KEY_DOWN:
    events.push_back(arcade::Events::DOWN);
    break;
  case KEY_RIGHT:
    events.push_back(arcade::Events::RIGHT);
    break;
  case KEY_LEFT:
    events.push_back(arcade::Events::LEFT);
    break;
  case KEY_C1:
    events.push_back(arcade::Events::CLOSE);
    break;
  case F2:
    events.push_back(arcade::Events::LIB_DOWN);
    break;
  case F3:
    events.push_back(arcade::Events::LIB_UP);
    break;
  case F4:
    events.push_back(arcade::Events::GAME_DOWN);
    break;
  case F5:
    events.push_back(arcade::Events::GAME_UP);
    break;
  case F8:
    events.push_back(arcade::Events::RESTART_GAME);
    break;
  case F9:
    events.push_back(arcade::Events::MENU);
    break;
    default:
      break;
  }
  return (events);
}

void Graphic::ArcadeCurses::sendMap(arcade::Map *map)
{
  _map = map;
  _mapEntities.clear();

  for (size_t i = 0; i < map->getSize(); i++)
    {
      _mapEntities.push_back((*map)[i]);
    }
}

void  Graphic::ArcadeCurses::printTriangle(int startrow, int startcol, int height)
{
  int x = startcol;

  for (int r = startrow; r <= startrow + height; r++)
  {
    for (int c = startcol; c <= x; c++)
    {
      if ((move(r, c)) == ERR)
        throw exception::GraphicError("move has failed");
      else if ((printw(" ")) == ERR)
        throw exception::GraphicError("printw has failed");
    }
    x++;
    startcol--;
  }
}

void  Graphic::ArcadeCurses::printRectangle(int startrow, int startcol, int height, int width)
{
  for(int r = startrow; r <= startrow + height; r++)
  {
    for(int c = startcol; c <= startcol + width; c++)
    {
      if ((move(r, c)) == ERR)
        throw exception::GraphicError("move has failed");
      else if ((printw(" ")) == ERR)
        throw exception::GraphicError("printw has failed");
    }
  }
}

void  Graphic::ArcadeCurses::printToScreen(int pos_x, int pos_y, const char c) const
{
  if ((mvwaddch(this->_wind, pos_x, pos_y, c)) == ERR)
    throw exception::GraphicError("mvwaddch has failed");
}

void Graphic::ArcadeCurses::sendScore(size_t score) {
  
  _score = score;
}