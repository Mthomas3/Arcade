#ifndef ARCADE_MAP_HH
# define ARCADE_MAP_HH

# include <list>
# include <vector>
# include "Entity.hh"
# include "../Protocol.hpp"
#include "Defines.hh"

namespace arcade
{
	struct Map
	{
		Map() { }
		Map(Size size, Size cell) : mapSize(size), cellSize(cell) { }

		Map &operator<<(Entity *entity) // Ajout d'un TileConfig à Map : Map << TileConfig#1 << TileConfig#2 ...
		{
			tileConfig.push_back(entity);
			return (*this);
		}
		Map &operator+=(TileType const &tile) // Ajout d'un Tile à la Map : Map += TileType::Empty
		{
			tileMap.push_back(tile);
			return (*this);
		}
		Entity *operator[](unsigned int index) // Recuperation du Entity directement depuis la map
		{
			return ((index < getSize() && (size_t) tileMap[index] < tileConfig.size()) ?
			        tileConfig[(size_t) tileMap[index]] : NULL);
		}

		unsigned int getLength() const { return mapSize.second; }
		unsigned int getWidth() const { return mapSize.first; }
		unsigned int getSize() const { return mapSize.first * mapSize.second; }
		bool isFilled() const { return getSize() <= tileMap.size(); }

		Size mapSize;
		Size cellSize;
		std::vector<Entity *> tileConfig;
		std::vector<TileType> tileMap;
	};
}

#endif //ARCADE_MAP_HH
