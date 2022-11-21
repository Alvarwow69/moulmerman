/*
** ShipWreck Engine , 2022
** SelectionPlayer.cpp
*/

#include "EndPlayer.hpp"

moul::EndPlayer::EndPlayer(sw::GameObject &gameObject) :
sw::Component(gameObject),
m_modelName("PLACEHOLDER"),
m_animName("Player_idle")
{
    m_gameObject.scene().eventManager["Start"].subscribe(m_gameObject.name(), this, &moul::EndPlayer::start);
    m_gameObject.scene().eventManager["Update"].subscribe(m_gameObject.name(), this, &moul::EndPlayer::update);
}

void moul::EndPlayer::start()
{
    m_mesh.emplace(m_gameObject.createComponent<sw::MeshRenderer>("MeshRendererManager", m_modelName));
    auto& animator = m_gameObject.createComponent<sw::ModelAnimator>("ModelAnimatorManager", m_animName);
    animator.attachModel(m_modelName);
    m_mesh.value().attachLight("DirLight");
    m_mesh.value().m_animator.emplace(animator);
}

void moul::EndPlayer::update()
{}