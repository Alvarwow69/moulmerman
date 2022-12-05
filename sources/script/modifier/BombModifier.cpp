/*
** ShipWreck Engine , 2022
** BombModifier.cpp
*/

#include "modifier/BombModifier.hpp"
#include "script/Player.hpp"

moul::BombModifier::BombModifier(sw::GameObject &gameObject) :
moul::Modifier(gameObject),
m_good(true)
{
    m_modelName = "";
}

void moul::BombModifier::applyModifier(moul::Player& player)
{
    if (m_good) {
        player.increaseMaxBomb();
    } else {
        player.increaseMaxBomb(1);
    }
    m_gameObject.scene().m_lut.erase(m_gameObject.id);
    m_gameObject.scene().m_tree.erase(m_gameObject.id);
    m_gameObject.scene().deleteGameObject(m_gameObject.name());
}