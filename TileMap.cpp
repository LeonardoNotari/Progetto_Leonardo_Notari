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
    std::string v[width*height];
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
    int counter = 0;
    for (auto & it : myVector)
    {
        v[counter]= it;
        counter++;

    }


    // dimensionare il vertex array per adeguarlo al livello
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);
    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; i++)
        for (unsigned int j = 0; j < height; j++)
        {
            int tileNumber;
            if (v[i+j*width]=="0")
                tileNumber=0;
            if (v[i+j*width]=="1")
                tileNumber=1;
            if (v[i+j*width]=="2")
                tileNumber=2;
            if (v[i+j*width]=="3")
                tileNumber=3;
            if (v[i+j*width]=="4")
                tileNumber=4;
            if (v[i+j*width]=="5")
                tileNumber=5;
            if (v[i+j*width]=="6")
                tileNumber=6;
            if (v[i+j*width]=="7")
                tileNumber=7;
            // load the tileset texture
            if (!m_tileset.loadFromFile(tileimg))
                return false;

            // trova la posizione in tileimg per il texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // puntatore al quadrato
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // vertici del quadrato
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // coordinate del texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

