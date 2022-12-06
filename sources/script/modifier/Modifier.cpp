/*
** ShipWreck Engine , 2022
** Modifier.cpp
*/

#include "OpenGLModule.hpp"

#include "modifier/Modifier.hpp"
#include "gameObject/GameObject.hpp"

moul::Modifier::Modifier(sw::GameObject &gameObject) :
sw::Component(gameObject),
m_animTime(0.0f)
{
    gameObject.scene().eventManager["Start"].subscribe(m_gameObject.name(), this, &moul::Modifier::start);
    gameObject.scene().eventManager["Update"].subscribe(m_gameObject.name(), this, &moul::Modifier::update);
}

moul::Modifier::~Modifier() noexcept
{
    m_gameObject.scene().eventManager["Start"].unsubscribe(m_gameObject.name());
    m_gameObject.scene().eventManager["Update"].unsubscribe(m_gameObject.name());

}

void moul::Modifier::start()
{
    auto size = sw::Vector2f{0.3f, 0.3f};
    auto& trans = m_gameObject.transform().getGlobalPosition();

    m_meshRenderer.emplace(m_gameObject.createComponent<sw::MeshRenderer>("MeshRendererManager", m_modelName));
    m_audioSource.emplace(m_gameObject.createComponent<sw::AudioSource>("AudioManager"));
    m_gameObject.transform().scale(0.5f, 0.5f, 0.5f);
    m_gameObject.scene().m_lut.emplace(m_gameObject.id, *this);
    m_gameObject.scene().m_tree.insert(m_gameObject.id, {trans.x - size.x, trans.z - size.y}, {trans.x + size.x, trans.z + size.y});
}

void moul::Modifier::update()
{
    m_gameObject.transform().rotate(90.0f * sw::OpenGLModule::deltaTime());
    m_animTime += sw::OpenGLModule::deltaTime();
    while (m_animTime > 2.0f)
        m_animTime -= 2.0f;
    auto t = m_animTime < 1.f ? m_animTime : 2.f - m_animTime;
    auto y = t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
    m_gameObject.transform().move(0, (y - 0.5f) * 0.075f, 0);
}