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
    bool readMatrix(const std::string &tileimg,const std::string &leveltxt, std::vector<Tile *> &tiles) ;
    bool loadMap(sf::Vector2u tileSize, unsigned int width, unsigned int height,std::vector<Tile *> &tiles) ;
protected:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override ;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif //MAPPA_TILE_TILEMAP_H
