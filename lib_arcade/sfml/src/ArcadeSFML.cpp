//
// Created by styvaether on 3/8/16.
//

#include "../include/ArcadeSFML.hh"

void Graphic::ArcadeSFML::init()
{
}

void Graphic::ArcadeSFML::display()
{
    if (_map == nullptr)
        return;
    for (int i = 0; i < _mapEntities.size(); i++)
    {
        _mapCoords[i]->setPosition((i % _map->getWidth()) * _map->cellSize.first,
                                   (i  / _map->getWidth()) * _map->cellSize.second);
        _mapCoords[i]->setRotation(_mapEntities[i]->angle);
        _window.draw(*_mapSprites[i]);
    }
    for (int i = 0; i < _entities.size(); i++)
    {
        switch (_entities[i]->shape.type)
        {
            case arcade::Type::SCIRCLE:
                _coords[i]->setPosition(_entities[i]->pos.first * _map->cellSize.first + 7,
                                        _entities[i]->pos.second * _map->cellSize.second + 7);
                break;
            case arcade::Type::BCIRCLE:
                _coords[i]->setPosition(_entities[i]->pos.first * _map->cellSize.first + 7,
                                        _entities[i]->pos.second * _map->cellSize.second + 7);
                break;
            default:
                _coords[i]->setPosition(_entities[i]->pos.first * _map->cellSize.first,
                                        _entities[i]->pos.second * _map->cellSize.second);
        }
        _coords[i]->setRotation(_entities[i]->angle);
        _window.draw(*_sprites[i]);
    }
    sf::Text text;
    sf::Font font;
    if (font.loadFromFile("arial.ttf"))
    {
        text.setFont(font);
        text.setString("Score : " + std::to_string(_score));
        text.setColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        text.setCharacterSize(24);

        _window.draw(text);
    }
    _window.display();
}

void Graphic::ArcadeSFML::createWindow(size_t x, size_t y)
{
    _window.create(sf::VideoMode(x, y), "Arcade");
}

void Graphic::ArcadeSFML::destroyWindow()
{
    _window.close();
}

std::list<arcade::Events> Graphic::ArcadeSFML::getEvents()
{
    std::list<arcade::Events> events;

    while (_window.pollEvent(_event))
    {
        switch (_event.type)
        {
            case sf::Event::Closed:
                events.push_back(arcade::Events::CLOSE);
                break;
            case sf::Event::KeyPressed:
                ManageKey(events, _event);
                break;
        }
    }
    return events;
}

void Graphic::ArcadeSFML::ManageKey(std::list<arcade::Events> &events, sf::Event event)
{
    switch (event.key.code)
    {
        case sf::Keyboard::Escape:
            events.push_back(arcade::Events::CLOSE);
            break;
        case sf::Keyboard::Up:
            events.push_back(arcade::Events::UP);
            break;
        case sf::Keyboard::Down:
            events.push_back(arcade::Events::DOWN);
            break;
        case sf::Keyboard::Left:
            events.push_back(arcade::Events::LEFT);
            break;
        case sf::Keyboard::Right:
            events.push_back(arcade::Events::RIGHT);
            break;
        case sf::Keyboard::F2:
            events.push_back(arcade::Events::LIB_DOWN);
            break;
        case sf::Keyboard::F3:
            events.push_back(arcade::Events::LIB_UP);
            break;
        case sf::Keyboard::F4:
            events.push_back(arcade::Events::GAME_DOWN);
            break;
        case sf::Keyboard::F5:
            events.push_back(arcade::Events::GAME_UP);
            break;
        case sf::Keyboard::F8:
            events.push_back(arcade::Events::RESTART_GAME);
            break;
        case sf::Keyboard::F9:
            events.push_back(arcade::Events::MENU);
            break;
    }
}

void Graphic::ArcadeSFML::setEntities(const std::vector<arcade::Entity *> &entities)
{
    for (sf::Drawable *draw : _sprites)
        delete draw;
    _sprites.clear();
    /*for (sf::Transformable *tr : _coords)
        delete tr;*/
    _coords.clear();
    _entities.clear();
    for (arcade::Entity *entity : entities)
    {
        _entities.push_back(entity);
        initSprite(*entity, _sprites, _coords);
    }
};

void Graphic::ArcadeSFML::initSprite(const arcade::Entity &entity, std::vector<sf::Drawable *> &sprites, std::vector<sf::Transformable *> &coords)
{
    sf::Texture *texture = new sf::Texture;

    if (entity.sprite && entity.sprite->path.size() > 0 && texture->loadFromFile(entity.sprite->path[0]))
    {
        sf::Sprite *sprite = new sf::Sprite(*texture);
        sprites.push_back(sprite);
        coords.push_back(sprite);
    }
    else
    {
        sf::Shape *shape;

        shape = _factory.createShape(entity.shape.type, entity.shape.color);
        if (shape != nullptr)
        {
            sprites.push_back(shape);
            coords.push_back(shape);
        }
    }
}

void Graphic::ArcadeSFML::sendMap(arcade::Map *map)
{
    _map = map;
    for (size_t i = 0; i < _mapCoords.size(); i++)
        delete _mapCoords[i];
    _mapEntities.clear();
    for (size_t i = 0; i < map->getSize(); i++)
    {
        _mapEntities.push_back((*map)[i]);
        initSprite(*(*map)[i], _mapSprites, _mapCoords);
    }
}

void Graphic::ArcadeSFML::sendScore(size_t score)
{
    _score = score;
}