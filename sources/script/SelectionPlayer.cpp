/*
** ShipWreck Engine , 2022
** SelectionPlayer.cpp
*/

#include "SelectionPlayer.hpp"
#include "config/Config.hpp"

moul::SelectionPlayer::SelectionPlayer(sw::GameObject &gameobject) :
sw::Component(gameobject),
m_modelName("PLACEHOLDER"),
m_must(false)
{
    m_gameObject.scene().eventManager["Start"].subscribe(m_gameObject.name(), this, &moul::SelectionPlayer::start);
    m_gameObject.scene().eventManager["Update"].subscribe(m_gameObject.name(), this, &moul::SelectionPlayer::update);
}

void moul::SelectionPlayer::start()
{
    m_mesh.emplace(m_gameObject.createComponent<sw::MeshRenderer>("MeshRendererManager", m_modelName));
    m_mesh.value().attachLight("DirLight");
    auto& animator = m_gameObject.createComponent<sw::ModelAnimator>("ModelAnimatorManager", "Player_idle");
    animator.attachModel(m_modelName);
    m_mesh.value().m_animator.emplace(animator);
    auto& text = m_gameObject.scene().createGameObject(m_gameObject.name() + "_Name");
    m_gameObject.addChild(m_gameObject.name() + "_Name");
    m_name.emplace(text.createComponent<moul::SelectionPlayerName>("ScriptManager"));
    m_name.value().m_playerName = m_gameObject.name();
    m_name.value().m_textPos = {m_textPos.x, m_textPos.y};
    m_name.value().start();
    auto& child = m_gameObject.scene().createGameObject(m_gameObject.name() + "_Type");
    m_gameObject.addChild(m_gameObject.name() + "_Type");
    m_type.emplace(child.createComponent<moul::SelectionPlayerType>("ScriptManager"));
    m_type.value().m_textPos = {m_textPos.x, m_textPos.y - 50};
    m_type.value().m_must = m_must;
    m_type.value().start();
}

void moul::SelectionPlayer::update()
{
    if (m_prevPlayer.hasValue()) {
        m_type.value().gameObject().setActive(m_prevPlayer.value().m_type.value().getType() != moul::SelectionPlayerType::NONE);
        m_name.value().gameObject().setActive(m_prevPlayer.value().m_type.value().getType() != moul::SelectionPlayerType::NONE);
    }
    if (m_type.value().getType() == moul::SelectionPlayerType::Type::NONE)
        m_mesh.value().setActive(false);
    else
        m_mesh.value().setActive(true);
}

void moul::SelectionPlayer::saveConf()
{
    sw::Config::GetConfig()["Setting"][m_gameObject.name()]["name"] = m_name.value().m_playerName;
    sw::Config::GetConfig()["Setting"][m_gameObject.name()]["type"] = m_type.value().getTypeName();
}