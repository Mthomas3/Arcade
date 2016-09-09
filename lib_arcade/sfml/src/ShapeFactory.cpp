//
// Created by gascon_n on 3/18/16.
//

#include "../include/ShapeFactory.hh"

Factory::ShapeFactory::ShapeFactory()
{
    _map[arcade::Type::SBOX] = &ShapeFactory::createSBox;
    _map[arcade::Type::BBOX] = &ShapeFactory::createBBox;
    _map[arcade::Type::SCIRCLE] = &ShapeFactory::createSCircle;
    _map[arcade::Type::BCIRCLE] = &ShapeFactory::createBCircle;
    _map[arcade::Type::TRIANGLE] = &ShapeFactory::createTriangle;
}

sf::Shape *Factory::ShapeFactory::createShape(arcade::Type shape, const arcade::Color &color) const
{
    std::map<arcade::Type, std::function<sf::Shape *(const ShapeFactory *, const arcade::Color &)>>::const_iterator it;

    it = _map.find(shape);
    if (it != _map.end())
        return (it->second(this, color));
    return nullptr;
}

sf::Shape *Factory::ShapeFactory::createSBox(const arcade::Color &color) const
{
    sf::Shape *box;

    box = new sf::RectangleShape(sf::Vector2f(5, 5));
    if (box != nullptr)
        box->setFillColor(sf::Color(static_cast<uint8_t>(std::get<0>(color)),
                                    static_cast<uint8_t>(std::get<1>(color)), static_cast<uint8_t>(std::get<2>(color))));
    return box;
}

sf::Shape *Factory::ShapeFactory::createBBox(const arcade::Color &color) const
{
    sf::Shape *box;

    box = new sf::RectangleShape(sf::Vector2f(20, 20));
    if (box != nullptr)
        box->setFillColor(sf::Color(static_cast<uint8_t>(std::get<0>(color)),
                                    static_cast<uint8_t>(std::get<1>(color)), static_cast<uint8_t>(std::get<2>(color))));
    return box;
}

sf::Shape *Factory::ShapeFactory::createBCircle(const arcade::Color &color) const
{
    sf::Shape *box;

    box = new sf::CircleShape(5);
    if (box != nullptr)
        box->setFillColor(sf::Color(static_cast<uint8_t>(std::get<0>(color)),
                                    static_cast<uint8_t>(std::get<1>(color)), static_cast<uint8_t>(std::get<2>(color))));
    return box;
}

sf::Shape *Factory::ShapeFactory::createSCircle(const arcade::Color &color) const
{
    sf::Shape *box;

    box = new sf::CircleShape(3);
    if (box != nullptr)
        box->setFillColor(sf::Color(static_cast<uint8_t>(std::get<0>(color)),
                                    static_cast<uint8_t>(std::get<1>(color)), static_cast<uint8_t>(std::get<2>(color))));
    return box;
}

sf::Shape *Factory::ShapeFactory::createTriangle(const arcade::Color &color) const
{
    sf::Shape *box;

    box = new sf::CircleShape(10, 3);
    if (box != nullptr)
        box->setFillColor(sf::Color(static_cast<uint8_t>(std::get<0>(color)),
                                    static_cast<uint8_t>(std::get<1>(color)), static_cast<uint8_t>(std::get<2>(color))));
    return box;
}