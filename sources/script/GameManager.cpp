/*
** ShipWreck Engine , 2022
** GameManager.cpp
*/

#include "script/GameManager.hpp"

moul::GameManager::GameManager(sw::GameObject &gameObject) :
sw::Component(gameObject),
m_mapGenerator()
{
    gameObject.scene().eventManager["Start"].subscribe(this, &moul::GameManager::start);
    gameObject.scene().eventManager["Update"].subscribe(this, &moul::GameManager::update);
}

void moul::GameManager::start()
{
    auto& mapGen = m_gameObject.scene().createGameObject("MapGenerator");
    m_mapGenerator.emplace(mapGen.createComponent<moul::MapGenerator>("ScriptManager"));
    m_mapGenerator.value().m_origin = {4.5f, 3.6f, -30};
    m_mapGenerator.value().generateMap(13, 13);
    m_mapGenerator.value().generateBasicMap();
    m_mapGenerator.value().generatePlayers(4);
    m_mapGenerator.value().generateVisual();
}

void moul::GameManager::update()
{

}