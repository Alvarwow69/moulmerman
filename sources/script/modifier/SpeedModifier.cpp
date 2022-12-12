/*
** ShipWreck Engine , 2022
** BombModifier.cpp
*/

#include "modifier/SpeedModifier.hpp"
#include "script/Player.hpp"
#include "script/AI.hpp"

moul::SpeedModifier::SpeedModifier(sw::GameObject &gameObject) :
moul::Modifier(gameObject),
m_good(true)
{
    m_modelName = "";
}

void moul::SpeedModifier::applyModifier(moul::AI& player)
{
    if (m_good) {
        player.increaseSpeed();
    }
    else {
        player.increaseSpeed(1);
    }
    m_gameObject.scene().m_lut.erase(m_gameObject.id);
    m_gameObject.scene().m_tree.erase(m_gameObject.id);
    m_gameObject.scene().deleteGameObject(m_gameObject.name());
}

void moul::SpeedModifier::applyModifier(moul::Player& player)
{
    if (m_good) {
        player.increaseSpeed();
    } else {
        player.increaseSpeed(1);
    }
    m_gameObject.scene().m_lut.erase(m_gameObject.id);
    m_gameObject.scene().m_tree.erase(m_gameObject.id);
    m_gameObject.scene().deleteGameObject(m_gameObject.name());
}