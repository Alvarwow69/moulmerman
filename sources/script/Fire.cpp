/*
** ShipWreck Engine, 2022
** Player.cpp
*/

#include "Fire.hpp"

moul::Fire::Fire(sw::GameObject& gameObject) :
sw::Component(gameObject),
m_spentTime(0.0f),
m_durationTime(3.0f)
{
    m_gameObject.scene().eventManager["Start"].subscribe(this, &moul::Fire::start);
    m_gameObject.scene().eventManager["Update"].subscribe(this, &moul::Fire::update);
}

void moul::Fire::start()
{
    m_mesh.emplace(m_gameObject.createComponent<sw::MeshRenderer>("MeshRendererManager", "Fire"));
}

void moul::Fire::update()
{
    double elapsedTime = sw::OpenGLModule::deltaTime();

    m_spentTime += elapsedTime;
    if (m_spentTime > m_durationTime)
        m_gameObject.setActive(false); //tscene().deleteGameObject(m_gameObject.name()); //TODO Remove event subscription
}