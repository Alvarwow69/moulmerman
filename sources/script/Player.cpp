/*
** ShipWreck Engine, 2022
** Player.cpp
*/

#include "Player.hpp"
#include "config/Config.hpp"

moul::Player::Player(sw::GameObject& gameObject) : sw::Component(gameObject), m_modelName("PLACEHOLDER")
{
    m_gameObject.scene().eventManager["Start"].subscribe(this, &moul::Player::start);
    m_gameObject.scene().eventManager["Update"].subscribe(this, &moul::Player::update);
}

bool moul::Player::isAlive() {
    return m_alive;
}

void moul::Player::setKeys()
{
    m_keys[m_actions::FORWARD] = sw::Config::GetConfig()["Setting"][m_gameObject.name()]["keys"]["f"].as<int>();
    m_keys[m_actions::BACKWARD] = sw::Config::GetConfig()["Setting"][m_gameObject.name()]["keys"]["b"].as<int>();
    m_keys[m_actions::LEFT] = sw::Config::GetConfig()["Setting"][m_gameObject.name()]["keys"]["l"].as<int>();
    m_keys[m_actions::RIGHT] = sw::Config::GetConfig()["Setting"][m_gameObject.name()]["keys"]["r"].as<int>();
    m_keys[m_actions::BOMB] = sw::Config::GetConfig()["Setting"][m_gameObject.name()]["keys"]["bomb"].as<int>();
}

void moul::Player::start()
{
    m_mesh.emplace(m_gameObject.createComponent<sw::MeshRenderer>("MeshRendererManager", m_modelName));
    m_alive = true;
    m_speed = 3.f;
    setKeys();
}

void moul::Player::update()
{
    float elapsedTime = sw::OpenGLModule::chrono().getElapsedTime();

    if (sw::isKeyDown(m_keys[m_actions::FORWARD])) {
        m_gameObject.transform().move(0, m_speed * elapsedTime, 0);
    }
    if (sw::isKeyDown(m_keys[m_actions::BACKWARD])) {
        m_gameObject.transform().move(0, -m_speed * elapsedTime, 0);
    }
    if (sw::isKeyDown(m_keys[m_actions::LEFT])) {
        m_gameObject.transform().move(-m_speed * elapsedTime, 0, 0);
    }
    if (sw::isKeyDown(m_keys[m_actions::RIGHT])) {
        m_gameObject.transform().move(m_speed * elapsedTime, 0, 0);
    }
    if (sw::isKeyDown(m_keys[m_actions::BOMB])) {
        bomb();
    }
    /*
    for (auto& it = *m_bombs.begin(); it != *m_bombs.end(); it++) {
    }
    */

}

void moul::Player::addBombNumber() {
    m_bombNumberTotal += 1;
    m_bombAvailable += 1;
}

void moul::Player::addBombPower() {
    m_bombPower += 1;
}

void moul::Player::bomb()
{
    if (m_bombAvailable < 1)
        return;
    m_bombAvailable -= 1;
    m_bombs.push_back(std::make_shared<Bomb>());
    return;
}

void moul::Player::die()
{
    m_gameObject.scene().eventManager.drop("PlayerDie");
    return;
}