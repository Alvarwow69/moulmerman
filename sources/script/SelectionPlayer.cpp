/*
** ShipWreck Engine , 2022
** SelectionPlayer.cpp
*/

#include "SelectionPlayer.hpp"

moul::SelectionPlayer::SelectionPlayer(sw::GameObject &gameobject) :
sw::Component(gameobject),
m_modelName("PLACEHOLDER"),
m_playerName("Player")
{
    m_gameObject.scene().eventManager["Start"].subscribe(this, &moul::SelectionPlayer::start);
    m_gameObject.scene().eventManager["Update"].subscribe(this, &moul::SelectionPlayer::update);
}

void moul::SelectionPlayer::start()
{
    m_mesh.emplace(m_gameObject.createComponent<sw::MeshRenderer>("MeshRendererManager", m_modelName));
    auto& text = m_gameObject.createComponent<sw::Text>("TextManager");
    text.setText(m_playerName).setPosition(m_textPos.x, m_textPos.y);
    auto& child = m_gameObject.scene().createGameObject(m_gameObject.name() + "_Type");
    m_gameObject.addChild(m_gameObject.name() + "_Type");
    m_type.emplace(child.createComponent<moul::SelectionPlayerType>("ScriptManager"));
    m_type.value().m_textPos = {m_textPos.x, m_textPos.y - 50};
    m_type.value().start();
}

void moul::SelectionPlayer::update()
{
    if (m_type.value().getType() == moul::SelectionPlayerType::Type::NONE)
        m_mesh.value().setActive(false);
    else
        m_mesh.value().setActive(true);
}