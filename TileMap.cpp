//
// Created by leonardo on 14/08/20.
//

#include <fstream>
#include <sstream>
#include "TileFactory.h"
#include "TileMap.h"


void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}


bool TileMap::readMatrix(const std::string &tileimg, const std::string &leveltxt, std::vector<Tile *> &tiles) {
    std::ifstream inputFile(leveltxt, std::ifstream::in);
    std::string auxString;
    TileFactory factoryT;
    float x = 0;
    float y = 0;
    if (!m_tileset.loadFromFile(tileimg))
        return false;
    while (std::getline(inputFile, auxString)) {
        std::stringstream stream(auxString);
        while (std::getline(stream, auxString, ';')) {
            //FIXME PROVA NUOVO VETTORE DI TILES
            if (auxString == " 2" || auxString == " 0" || auxString == " 1" || auxString == " 8" || auxString == " 9")
                tiles.push_back(factoryT.createTile(TileType::topRockTile, auxString, x, y));
            if (auxString == " 4" || auxString == " 5" || auxString == " 6")
                tiles.push_back(factoryT.createTile(TileType::lavaTile, auxString, x, y));
            if (auxString == "13")
                tiles.push_back(factoryT.createTile(TileType::backgroundTile, auxString, x, y));
            if (auxString == " 3" || auxString == " 7" || auxString == "10")
                tiles.push_back(factoryT.createTile(TileType::tipsRockTile, auxString, x, y));

            x += 64;
            if (x == 8192) {
                y += 64;
                x = 0;
            }
        }
    }
    return true;
}

bool TileMap::loadMap(sf::Vector2u tileSize, unsigned int width, unsigned int height, std::vector<Tile *> &tiles) {
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);
    // populate the vertex array, with one quad per tile
    auto it = tiles.begin();
    Tile *tile;
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            int tileNumber;
            std::stringstream s1;
            tile = *it;
            s1 << tile->code;
            it++;
            s1 >> tileNumber;
            // trova la posizione in tileimg per il texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // puntatore al quadrato
            sf::Vertex *quad = &m_vertices[(j + i * width) * 4];

            // vertici del quadrato
            quad[0].position = sf::Vector2f(tile->xVertexTopSx, tile->yVertexTopSx);
            quad[1].position = sf::Vector2f(tile->xVertexTopSx + 64, tile->yVertexTopSx);
            quad[2].position = sf::Vector2f(tile->xVertexTopSx + 64, tile->yVertexTopSx + 64);
            quad[3].position = sf::Vector2f(tile->xVertexTopSx, tile->yVertexTopSx + 64);
            // coordinate del texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
    return true;
}
