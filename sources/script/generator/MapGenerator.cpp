/*
** ShipWreck Engine , 2022
** MapGenerator.cpp
*/

#include "generator/MapGenerator.hpp"
#include "OpenGLModule.hpp"
#include "components/Components.hpp"

moul::MapGenerator::MapGenerator(sw::GameObject &gameObject) :
sw::Component(gameObject),
m_size(),
m_map(),
m_basic(false),
m_origin{0, 0, 0}
{}

void moul::MapGenerator::generateMap(int with, int height)
{
    std::string tmp;
    m_size.x = with;
    m_size.y = height;

    tmp.clear();
    for (int y = 0; y < m_size.x + 2; y++)
        tmp.append("*");
    tmp.append("\n");
    m_map.emplace_back(tmp);

    for (int x = 0; x < m_size.x; x++) {
        tmp.clear();
        tmp.append("*");
        for (int y = 0; y < m_size.y; y++)
            tmp.append(" ");
        tmp.append("*\n");
        m_map.emplace_back(tmp);
    }
    tmp.clear();
    for (int y = 0; y < m_size.x + 2; y++)
        tmp.append("*");
    tmp.append("\n");
    m_map.emplace_back(tmp);
}

void moul::MapGenerator::generateProcedural()
{
    m_basic = false;
}

void moul::MapGenerator::generateBasicMap()
{
    std::string tmp;

    m_basic = true;
    m_map.clear();
    tmp.clear();
    for (int y = 0; y < m_size.x + 2; y++)
        tmp.append("*");
    tmp.append("\n");
    m_map.emplace_back(tmp);

    for (int x = 0; x < m_size.x; x++) {
        tmp.clear();
        tmp.append("*");
        for (int y = 0; y < m_size.y; y++)
            if (y % 2 && x % 2)
                tmp.append("*");
            else
                tmp.append(" ");
        tmp.append("*\n");
        m_map.emplace_back(tmp);
    }
    tmp.clear();
    for (int y = 0; y < m_size.x + 2; y++)
        tmp.append("*");
    tmp.append("\n");
    m_map.emplace_back(tmp);
}

void moul::MapGenerator::generateVisual()
{
    int x = 0;
    int y = 0;
    for (const auto& line : m_map) {
        for (auto c : line) {
            auto& newBlock = m_gameObject.scene().createGameObject("Cube" + std::to_string(x) + "-" + std::to_string(y));
            newBlock.transform().setPosition(m_origin.x + (float)x, m_origin.y, m_origin.z + (float)y);
            switch (c) {
                case '*':
                    newBlock.createComponent<sw::MeshRenderer>("MeshRendererManager", "Unbreakable_Block");
                    break;
                case ' ':
                    newBlock.createComponent<sw::MeshRenderer>("MeshRendererManager", "Block");
                    break;
                default:
                    break;
            }
            x++;
        }
        y++;
        x = 0;
    }
}

void moul::MapGenerator::generatePlayers(int playerNbr)
{
    if (m_basic) {
        processBasicPlayers(playerNbr);
    } else {
        processNonBasicPlayers(playerNbr);
    }
}

const std::vector<std::string>& moul::MapGenerator::getMap() const
{
    return (m_map);
}

void moul::MapGenerator::processBasicPlayers(int playerNbr)
{
    m_map[1][1] = 'p';
    m_map[1][2] = 'e';
    m_map[2][1] = 'e';
    m_map[m_size.y][m_size.x] = 'p';
    m_map[m_size.y][m_size.x - 1] = 'e';
    m_map[m_size.y - 1][m_size.x] = 'e';
    if (playerNbr >= 3) {
        m_map[1][m_size.x] = 'p';
        m_map[1][m_size.x - 1] = 'e';
        m_map[2][m_size.x] = 'e';
    }
    if (playerNbr >= 4) {
        m_map[m_size.y][1] = 'p';
        m_map[m_size.y][2] = 'e';
        m_map[m_size.y - 1][1] = 'e';
    }
}

void moul::MapGenerator::processNonBasicPlayers(int playerNbr)
{

}