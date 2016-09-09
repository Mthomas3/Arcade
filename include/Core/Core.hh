//
// Created by gascon_n on 3/24/16.
//

#ifndef ARCADE_CORE_HH
#define ARCADE_CORE_HH

#include <Modules/IOInterface.hh>
#include <Modules/IGame.hh>
#include "DLLoader.hh"
#include "Time.hh"

namespace Core
{
    class Core
    {
    public:
        Core(char *path);
        virtual ~Core();
        virtual void loop();

    private:
        void initGraphics();
        void initGame();
        void scanGame();
        void scanLib();
        void setGame(const std::list<arcade::Events> &events);
        void setLib(const std::list<arcade::Events> &events);

        Loader::DLLoader<arcade::IOInterface> *_graphicLoader;
        Loader::DLLoader<arcade::IGame> *_gameLoader;
        std::vector<std::string > _gameVec;
        std::vector<std::string > _libVec;
        arcade::IOInterface *_graphic;
        arcade::IGame *_game;
        Pulse::Utils::Time *_time;
        int _indiceGame;
        int _indiceLib;
        bool _signal;
    };
}

#endif //ARCADE_CORE_HH
