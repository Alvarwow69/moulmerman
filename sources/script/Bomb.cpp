/*
** ShipWreck Engine, 2022
** Player.cpp
*/

#include "Bomb.hpp"
#include "config/Config.hpp"

moul::Bomb::Bomb(sw::GameObject& gameObject) : sw::Component(gameObject), m_modelName("PLACEHOLDER")
{
    m_gameObject.scene().eventManager["Start"].subscribe(this, &moul::Bomb::start);
    m_gameObject.scene().eventManager["Update"].subscribe(this, &moul::Bomb::update);
}

void moul::Bomb::start()
{
    m_mesh.emplace(m_gameObject.createComponent<sw::MeshRenderer>("MeshRendererManager", m_modelName));
}

void moul::Bomb::update()
{
    float elapsedTime = sw::OpenGLModule::chrono().getElapsedTime();

    m_spentTime += elapsedTime;

    if (m_spentTime > m_explosionTime) {
        explode();
    }
}

void moul::Bomb::destroy()
{
    return;
}

bool moul::Bomb::hasExploded() {
    return m_hasExploded;
}

void moul::Bomb::explode()
{
    m_hasExploded = true;
    return;
}