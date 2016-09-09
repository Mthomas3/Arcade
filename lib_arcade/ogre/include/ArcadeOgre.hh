//
// Created by mart_4 on 3/22/16.
//

#ifndef ARCADE_ARCADECURSES_H
#define ARCADE_ARCADECURSES_H

#include <ncurses.h>
#include <iostream>
#include <Ogre/Ogre.h>
#include <Modules/IOInterface.hh>
#include <OIS/OIS.h>

namespace Graphic
{
    class ArcadeOgre : public arcade::IOInterface, OIS::KeyListener
    {

    public :
        ArcadeOgre();
        virtual ~ArcadeOgre() { }
        virtual void init();
        virtual void display();
        virtual void createWindow(size_t x, size_t y);
        virtual void destroyWindow();
        virtual void setEntities(const std::vector<arcade::Entity *> &entities);
        virtual std::list<arcade::Events> getEvents();
        virtual void sendMap(arcade::Map *map);

        virtual bool keyPressed(const OIS::KeyEvent& ke);
        virtual bool keyReleased(const OIS::KeyEvent& ke);

        virtual void sendScore(size_t score) {}

    private :
        void DestroyAllAttachedMovableObjects(Ogre::SceneNode *);

        int         _key;
        arcade::Map *_map;
        Ogre::Root  *_root;
        Ogre::RenderWindow *_window;
        OIS::InputManager   *_input;
        OIS::Keyboard       *_keyboard;
        std::list<arcade::Events> _events;
        Ogre::SceneManager  *_manager;
        Ogre::Camera        *_cam;
        Ogre::Viewport      *_viewport;
        std::vector<Ogre::SceneNode *> _mapEntities;
        std::vector<Ogre::SceneNode *> _entities;
    };
}

#endif //ARCADE_ARCADECURSES_H
