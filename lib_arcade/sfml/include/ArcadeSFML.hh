//
// Created by styvaether on 3/8/16.
//

#ifndef ARCADE_ARCADESFML_HH
#define ARCADE_ARCADESFML_HH

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../../../include/Modules/IOInterface.hh"
#include "../include/ShapeFactory.hh"

namespace Graphic
{
    class ArcadeSFML : public arcade::IOInterface
    {
    public:
        ArcadeSFML() : _map(nullptr), _score(0) { }

        virtual ~ArcadeSFML()
        {
            for (size_t i = 0; i < _sprites.size(); i++)
                delete _sprites[i];
            _sprites.clear();
            _coords.clear();
            _entities.clear();
            _mapEntities.clear();
            for (size_t i = 0; i < _mapCoords.size(); i++)
                delete _mapCoords[i];
            _mapCoords.clear();
            _mapSprites.clear();
        }

        virtual void init();
        virtual void display();
        virtual void createWindow(size_t x, size_t y);
        virtual void destroyWindow();
        virtual void setEntities(const std::vector<arcade::Entity *> &entities);
        virtual std::list<arcade::Events> getEvents();
        virtual void sendMap(arcade::Map *map);
        virtual void sendScore(size_t score);

    private:
        void ManageKey(std::list<arcade::Events> &events, sf::Event);
        void initSprite(const arcade::Entity &entity, std::vector<sf::Drawable *> &sprites, std::vector<sf::Transformable *> &coords);

        sf::RenderWindow _window;
        sf::Event _event;
        Factory::ShapeFactory _factory;
        std::vector<sf::Drawable *> _sprites;
        std::vector<sf::Transformable *> _coords;
        std::vector<arcade::Entity *> _entities;
        std::vector<arcade::Entity *> _mapEntities;
        std::vector<sf::Drawable *> _mapSprites;
        std::vector<sf::Transformable *> _mapCoords;
        arcade::Map *_map;
        size_t _score;
    };
}

#endif //ARCADE_ARCADESFML_HH
