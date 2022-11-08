/*
** ShipWreck Engine , 2022
** MapGenerator.cpp
*/

#include "generator/MapGenerator.hpp"
#include "OpenGLModule.hpp"
#include "components/Components.hpp"

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

}

void moul::MapGenerator::generateBasicMap()
{
    std::string tmp;

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
            auto& newBlock = sw::OpenGLModule::sceneManager().getActiveScene()->createGameObject("Cube" + std::to_string(x) + "-" + std::to_string(y));
            newBlock.transform().setPosition(x, 0, y);
            newBlock.transform().setScale(6.3f, 6.3f, 6.3f);
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