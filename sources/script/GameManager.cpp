/*
** ShipWreck Engine , 2022
** GameManager.cpp
*/

#include "script/GameManager.hpp"

moul::GameManager::GameManager(sw::GameObject &gameObject) :
sw::Component(gameObject)
{
    gameObject.scene().eventManager["Start"].subscribe(this, &moul::GameManager::start);
    gameObject.scene().eventManager["Update"].subscribe(this, &moul::GameManager::update);
}

void moul::GameManager::start()
{
    m_mapGenerator.generateMap(13, 13);
    m_mapGenerator.generateBasicMap();
    m_mapGenerator.generateVisual();
}

void moul::GameManager::update()
{

}