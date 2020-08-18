//
// Created by leonardo on 14/08/20.
//

#include <fstream>
#include <sstream>
#include "TileMap.h"


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}


bool TileMap::load(const std::string &tileimg,sf::Vector2u tileSize, const std::string &leveltxt, unsigned int width, unsigned int height)
{
    std::ifstream inputFile (leveltxt, std::ifstream::in);
    std::vector<std::string> myVector;
    std::string auxString;
    while (std::getline (inputFile, auxString))
    {
        std::stringstream stream (auxString);
        while (std::getline (stream, auxString, ';'))
        {
            myVector.push_back (auxString);
        }
    }
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);
    // populate the vertex array, with one quad per tile
    auto it=myVector.begin();
    for (unsigned int i= 0; i < height; i++)
        for (unsigned int j = 0; j <width; j++)
        {
            int tileNumber;
            std::stringstream s1;
            s1<<*it;
            it++;
            s1 >> tileNumber;
            // load the tileset texture
            if (!m_tileset.loadFromFile(tileimg))
                return false;
            // trova la posizione in tileimg per il texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // puntatore al quadrato
            sf::Vertex* quad = &m_vertices[(j + i * width) * 4];

            // vertici del quadrato
            quad[0].position = sf::Vector2f(j * tileSize.y, i * tileSize.x);
            quad[1].position = sf::Vector2f((j + 1) * tileSize.y, i * tileSize.x);
            quad[2].position = sf::Vector2f((j + 1) * tileSize.y, (i + 1) * tileSize.x);
            quad[3].position = sf::Vector2f(j * tileSize.y, (i + 1) * tileSize.x);

            // coordinate del texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

