/*
** ShipWreck Engine , 2022
** NinjaModifier.cpp
*/

#include "modifier/NinjaModifier.hpp"
#include "script/Player.hpp"

moul::NinjaModifier::NinjaModifier(sw::GameObject &gameObject) :
moul::Modifier(gameObject),
m_good(true)
{
    m_modelName = "";
}

void moul::NinjaModifier::applyModifier(moul::Player& player)
{
    player.ninja();
    m_gameObject.scene().m_lut.erase(m_gameObject.id);
    m_gameObject.scene().m_tree.erase(m_gameObject.id);
    m_gameObject.scene().deleteGameObject(m_gameObject.name());
}