//
// Created by gascon_n on 3/18/16.
//

#ifndef ARCADE_SHAPEFACTORY_HH
# define ARCADE_SHAPEFACTORY_HH

# include <map>
# include <functional>
# include <SFML/Graphics.hpp>
# include <Core/Shape.hh>

namespace Factory
{
    class ShapeFactory
    {
    public:
        ShapeFactory();

        sf::Shape *createShape(arcade::Type shape, const arcade::Color &) const;

    private:
        sf::Shape *createSBox(const arcade::Color &) const;
        sf::Shape *createBBox(const arcade::Color &) const;
        sf::Shape *createSCircle(const arcade::Color &) const;
        sf::Shape *createBCircle(const arcade::Color &) const;
        sf::Shape *createTriangle(const arcade::Color &) const;

        std::map<arcade::Type, std::function<sf::Shape *(const ShapeFactory *, const arcade::Color &)>> _map;
    };
}

#endif //ARCADE_SHAPEFACTORY_HH
