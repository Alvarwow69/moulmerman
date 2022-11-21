/*
** ShipWreck Engine, 2022
** Player.cpp
*/

#include "Bomb.hpp"
#include "config/Config.hpp"
#include "Fire.hpp"
#include "GameManager.hpp"

const int xIndex[4] = {1, 0, -1, 0};
const int zIndex[4] = {0, 1, 0, -1};

moul::Bomb::Bomb(sw::GameObject& gameObject) :
sw::Component(gameObject),
m_modelName("Bomb"),
m_animTime(0.0f),
m_explosionTime(3.0f),
m_hasExploded(false),
m_power(4),
m_spentTime(0.0f),
m_lastTime(0.0f)
{
    m_gameObject.scene().eventManager["Start"].subscribe(m_gameObject.name(), this, &moul::Bomb::start);
    m_gameObject.scene().eventManager["Update"].subscribe(m_gameObject.name(), this, &moul::Bomb::update);
}

moul::Bomb::~Bomb() noexcept
{
    m_gameObject.scene().eventManager["Start"].unsubscribe(m_gameObject.name());
    m_gameObject.scene().eventManager["Update"].unsubscribe(m_gameObject.name());
}

void moul::Bomb::start()
{
    m_mesh.emplace(m_gameObject.createComponent<sw::MeshRenderer>("MeshRendererManager", m_modelName));
    m_audio.emplace(m_gameObject.createComponent<sw::AudioSource>("AudioManager"));
    m_audio.value().addAudio("UI_Bomb_tick").addAudio("UI_Bomb_tick2").addAudio("UI_Bomb_tick3").addAudio("UI_Bomb_tick4");
}

void moul::Bomb::update()
{
    double elapsedTime = sw::OpenGLModule::deltaTime();

    m_animTime += elapsedTime;
    while (m_animTime > 2.0f)
        m_animTime -= 2.0f;
    auto t = m_animTime < 1.f ? m_animTime : 2.f - m_animTime;
    auto y = t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;

    m_gameObject.transform().setScale(y * 0.5f + 1, y * 0.5f + 1, y * 0.5f + 1);

    m_spentTime += elapsedTime;
    double time;
    std::modf(m_spentTime, &time);
    if (time == m_lastTime && !hasExploded()) {
        m_lastTime += 1;
        m_audio.value().play();
    }
    if (m_spentTime > m_explosionTime && !hasExploded())
        explode();
}

void moul::Bomb::destroy()
{
    m_mesh.value().setActive(false);
}

bool moul::Bomb::hasExploded()
{
    return m_hasExploded;
}

void moul::Bomb::explode()
{
    bool border[4] = {false, false, false, false};
    m_hasExploded = true;
    m_gameObject.scene().deleteGameObject(m_gameObject.name());
    m_audio.value().play("UI_Bomb_explode");
    auto currentPos = m_gameObject.transform().getGlobalPosition();
    auto &newFire = m_gameObject.scene().createGameObject("Fire_" + m_gameObject.name() + "_" + std::to_string(currentPos.x) + "_" + std::to_string(currentPos.z));
    newFire.createComponent<moul::Fire>("ScriptManager").start();
    newFire.transform().setPosition(currentPos.x, currentPos.y, currentPos.z);
    newFire.transform().setScale(3, 3, 3);
    for (int i = 1; i <= m_power; i++) {
        for (int p = 0; p < 4; p++) {
            auto& map = moul::GameManager::GetMap().getMap();
            auto& origin = moul::GameManager::GetMap().m_origin;
            if (border[p] || map[(currentPos.x - origin.x) + i * xIndex[p]].at((currentPos.z - origin.z) + i * zIndex[p] + 1) == '*') {
                border[p] = true;
                continue;
            }
            auto &newFire = m_gameObject.scene().createGameObject("Fire_" + m_gameObject.name() + "_" + std::to_string(currentPos.x + i * xIndex[p]) + "_" + std::to_string(currentPos.z + i * zIndex[p]));
            newFire.createComponent<moul::Fire>("ScriptManager").start();
            newFire.transform().setPosition(currentPos.x + i * xIndex[p], currentPos.y, currentPos.z + i * zIndex[p]);
            newFire.transform().setScale(3, 3, 3);
        }
    }
}