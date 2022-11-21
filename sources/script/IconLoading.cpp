/*
** Society: Creative Rift
** SHIPWRECK ENGINE, 2022
** Author: Guillaume S.
** File name: Player.cpp
** Description: [CHANGE]
*/

#include "components/Components.hpp"
#include "event/EventCollision.hpp"

#include "script/IconLoading.hpp"
#include "OpenGLModule.hpp"

moul::IconLoading::IconLoading(sw::GameObject &gameObject) :
sw::Component(gameObject),
m_animTime(0.0f)
{
    m_gameObject.scene().eventManager["Start"].subscribe(m_gameObject.name(), this, &moul::IconLoading::start);
    m_gameObject.scene().eventManager["Update"].subscribe(m_gameObject.name(), this, &moul::IconLoading::update);
}

void moul::IconLoading::start()
{
    auto& sprite = m_gameObject.createComponent<sw::Sprite>("SpriteManager");
    std::string ye("Loading_icon");

    m_gameObject.transform().setPosition(1700, 875);
    sprite.setTexture(ye);
}

void moul::IconLoading::update()
{
    auto time = sw::OpenGLModule::deltaTime();
    m_animTime += time;
    while (m_animTime > 2.0f)
        m_animTime -= 2.0f;
    auto t = m_animTime < 1.f ? m_animTime : 2.f - m_animTime;
    auto y = t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;

    m_gameObject.transform().move(0, y - 0.5f, 0);
}