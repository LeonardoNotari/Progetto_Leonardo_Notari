//
// Created by leonardo on 13/07/20.
//

#ifndef MAPPA_TILE_TILEMAP_H
#define MAPPA_TILE_TILEMAP_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Tile.h"


class TileMap : public sf::Drawable, public sf::Transformable {
public:

    bool load(const std::string &tileimg,sf::Vector2u tileSize, const std::string &leveltxt, unsigned int width, unsigned int height,std::vector<Tile *> tiles) ;

protected:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override ;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif //MAPPA_TILE_TILEMAP_H
