//
// Created by gascon_n on 3/24/16.
//

#include <algorithm>
#include "../../include/Core/Core.hh"
#include <dirent.h>
#include <csignal>

static bool s_signal = false;

Core::Core::Core(char *path) : _graphic(nullptr), _game(nullptr), _graphicLoader(new Loader::DLLoader<arcade::IOInterface>(path, "getGraphic")), _gameLoader(new Loader::DLLoader<arcade::IGame>("./games/lib_snake_games.so", "getGame"))
{
    int i = 0;
    scanGame();
    scanLib();
    _signal = false;
    for (i = 0; i < _libVec.size();i++)
        if (_libVec[i].find(std::string(path)) != std::string::npos)
            break;
    _indiceGame = 0;
    _indiceLib = i;
    _graphicLoader->Open();
    _gameLoader->Open(RTLD_NOW);
    _graphic = _graphicLoader->GetInstance();
    _game = _gameLoader->GetInstance();
    if (!_graphic)
        throw exception::DLError("Failed to load graphic library.");
    initGraphics();
    if (!_game)
        throw exception::DLError("Failed to load game library.");
    initGame();
    _time = Pulse::Utils::Time::GetInstance();
}

void Core::Core::scanGame() {
    DIR *dir = opendir("games");

    if (dir != NULL)
    {
        struct dirent * ent;

        while ((ent = readdir(dir)) != NULL)
        {
            std::string name(ent->d_name);
            if (name.find("lib") == 0)
                _gameVec.push_back(name);
        }

        closedir(dir);
    }
}

void Core::Core::scanLib() {
    DIR *dir = opendir("lib");

    if (dir != NULL)
    {
        struct dirent * ent;

        while ((ent = readdir(dir)) != NULL)
        {
            std::string name(ent->d_name);
            if (name.find("lib_arcade_") == 0)
               _libVec.push_back(name);
        }
        closedir(dir);
    }
}

Core::Core::~Core()
{
    if (_graphic)
        _graphic->destroyWindow();
    _graphicLoader->Close();
}

void Core::Core::initGraphics()
{
    _graphic->init();
    _graphic->createWindow(800, 600);
}

void Core::Core::initGame()
{
    if (_game)
        _game->init();
}

void Core::Core::setGame(const std::list<arcade::Events> &events) {
    if (std::find(events.begin(), events.end(), arcade::Events::GAME_UP) != events.end()) {
        if (_indiceGame + 1 <= _gameVec.size() - 1)
            _indiceGame++;
        else
            _indiceGame = 0;
    }
    else {
        if (_indiceGame - 1 >= 0)
            _indiceGame--;
        else
            _indiceGame = _gameVec.size() - 1;
    }
        _graphic->destroyWindow();
        if (_gameLoader)
            delete _gameLoader;
        _gameLoader = new Loader::DLLoader<arcade::IGame>("./games/" + _gameVec[_indiceGame], "getGame");
        _gameLoader->Open(RTLD_NOW);
        if (_graphic)
            delete _graphic;
        _graphic = _graphicLoader->GetInstance();
        if (_game)
            delete _game;
        _game = _gameLoader->GetInstance();
        if (!_graphic)
            throw exception::DLError("Failed to load graphic library.");
        initGraphics();
        if (!_game)
            throw exception::DLError("Failed to load game library.");
        initGame();
        if (_graphic != nullptr && _game != nullptr)
            _graphic->sendMap(_game->getMap());
}
void Core::Core::setLib(const std::list<arcade::Events> &events) {
    if (std::find(events.begin(), events.end(), arcade::Events::LIB_UP) != events.end()) {
        if (_indiceLib + 1 <= _libVec.size() - 1)
            _indiceLib++;
        else
            _indiceLib = 0;
    }
    else {
        if (_indiceLib - 1 >= 0)
            _indiceLib--;
        else
            _indiceLib = _libVec.size() - 1;
    }
        _graphic->destroyWindow();
        if(_graphicLoader)
            delete _graphicLoader;
        if (_graphic)
            delete _graphic;
        _graphicLoader = new Loader::DLLoader<arcade::IOInterface>("lib/" + _libVec[_indiceLib], "getGraphic");
        _graphicLoader->Open();
        _graphic = _graphicLoader->GetInstance();
        if (!_graphic)
            throw exception::DLError("Failed to load graphic library.");
        initGraphics();
        if (_graphic != nullptr && _game != nullptr)
            _graphic->sendMap(_game->getMap());
}

void signal_handler(int signal)
{
    s_signal = true;
}

void Core::Core::loop()
{
    if (_graphic != nullptr && _game != nullptr)
        _graphic->sendMap(_game->getMap());
    while (true)
    {
        if (_graphic)
        {
            std::signal(SIGINT,signal_handler);
            std::signal(SIGWINCH, signal_handler);
            if (s_signal)
                   break;
            std::list<arcade::Events> events = _graphic->getEvents();
            if (std::find(events.begin(), events.end(), arcade::Events::GAME_UP) != events.end() ||
                        (std::find(events.begin(), events.end(), arcade::Events::GAME_DOWN) != events.end()))
                setGame(events);
            if (std::find(events.begin(), events.end(), arcade::Events::LIB_UP) != events.end() ||
                (std::find(events.begin(), events.end(), arcade::Events::LIB_DOWN) != events.end())) {
                setLib(events);
            }
            if (std::find(events.begin(), events.end(), arcade::Events::CLOSE) != events.end())
                break;
            _time->Update();
            if (_game)
            {
                _game->sendEvent(events);
                _graphic->sendScore(_game->getScore());
                _graphic->setEntities(_game->getEntities());
                _game->update(_time->DeltaTime);
            }
            _graphic->display();
        }
    }
}







