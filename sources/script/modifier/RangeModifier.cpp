/*
** ShipWreck Engine , 2022
** BombModifier.cpp
*/

#include "modifier/RangeModifier.hpp"
#include "script/Player.hpp"

moul::RangeModifier::RangeModifier(sw::GameObject &gameObject) :
moul::Modifier(gameObject),
m_good(true)
{
    m_modelName = "";
}

void moul::RangeModifier::applyModifier(moul::Player& player)
{
    if (m_good) {
        player.increaseBombPower();
    } else {
        player.increaseBombPower(1);
    }
    m_gameObject.scene().m_lut.erase(m_gameObject.id);
    m_gameObject.scene().m_tree.erase(m_gameObject.id);
    m_gameObject.scene().deleteGameObject(m_gameObject.name());
}