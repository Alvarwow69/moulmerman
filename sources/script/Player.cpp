/*
** ShipWreck Engine, 2022
** Player.cpp
*/

#include <iostream>

#include "Player.hpp"
#include "config/Config.hpp"

#include <memory_resource> //magic trick

moul::Player::Player(sw::GameObject& gameObject) :
sw::Component(gameObject),
m_modelName("PLACEHOLDER"),
m_bombAvailable(1)
{
    m_gameObject.scene().eventManager["Update"].subscribe(m_gameObject.name(), this, &moul::Player::update);
}

bool moul::Player::isAlive()
{
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
    m_animator.emplace(m_gameObject.createComponent<sw::ModelAnimator>("ModelAnimatorManager", "Player_idle"));
    m_animator.value().attachModel(m_modelName);
    m_mesh.value().m_animator.emplace(m_animator.value());
    m_alive = true;
    m_speed = 3.f;
    //m_collider.emplace(m_gameObject.createComponent<sw::BoxCollider>("BoxColliderManager"));
    //m_collider.value().setSize(1.0f, 1.0f);
    setKeys();
}

void moul::Player::updateAnimation()
{
    if (sw::isKeyPressed(m_keys[m_actions::FORWARD]) || sw::isKeyPressed(m_keys[m_actions::BACKWARD]) ||
        sw::isKeyPressed(m_keys[m_actions::LEFT]) || sw::isKeyPressed(m_keys[m_actions::RIGHT]))
        m_animator.value().playAnimation("Player_walk");
    if (sw::isKeyUp(m_keys[m_actions::FORWARD]) && sw::isKeyUp(m_keys[m_actions::BACKWARD]) &&
        sw::isKeyUp(m_keys[m_actions::LEFT]) && sw::isKeyUp(m_keys[m_actions::RIGHT]))
        m_animator.value().playAnimation("Player_idle");

}

void moul::Player::update()
{
    double elapsedTime = sw::OpenGLModule::deltaTime();
    
    std::array<std::byte, sizeof(size_t) * 256> buffer; // enough to fit in all nodes
    std::pmr::monotonic_buffer_resource mbr{buffer.data(), buffer.size()};
    std::pmr::polymorphic_allocator<int> pa{&mbr};
    std::pmr::list<int> list{pa};

    //std::vector<int> candidates;
    auto &tmp = m_gameObject.transform().getGlobalPosition();
    sw::Vector2f min{};
    sw::Vector2f max{};

    if (sw::isKeyDown(m_keys[m_actions::FORWARD])) {
        min = {tmp.z - 0.25f, (tmp.x - 0.25f) + static_cast<float>(m_speed * elapsedTime)};
        max = {min.x + 0.50f, (min.y + 0.50f)};
        m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
        if (!list.size())
        {
            m_gameObject.transform().move(0, 0, m_speed * elapsedTime);
            m_gameObject.transform().setRotation(0);
        }
    } else if (sw::isKeyDown(m_keys[m_actions::BACKWARD])) {
        min = {tmp.z - 0.25f, (tmp.x - 0.25f) + static_cast<float>(-m_speed * elapsedTime)};
        max = {min.x + 0.50f, (min.y + 0.50f)};
        m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
        if (!list.size())
        {
            m_gameObject.transform().move(0, 0, -m_speed * elapsedTime);
            m_gameObject.transform().setRotation(180);
        }
    } else if (sw::isKeyDown(m_keys[m_actions::LEFT])) {
        min = {(tmp.z - 0.25f) + static_cast<float>(m_speed * elapsedTime), (tmp.x - 0.25f)};
        max = {(min.x + 0.50f), (min.y + .50f)};
        m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
        if (!list.size())
        {
            m_gameObject.transform().move(m_speed * elapsedTime, 0, 0);
            m_gameObject.transform().setRotation(90);
        }
    } else if (sw::isKeyDown(m_keys[m_actions::RIGHT])) {
        min = {(tmp.z - 0.25f) + static_cast<float>(-m_speed * elapsedTime), (tmp.x - 0.25f)};
        max = {(min.x + 0.50f), (min.y + 0.50f)};
        m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
        if (!list.size())
        {
            m_gameObject.transform().move(-m_speed * elapsedTime, 0, 0);
            m_gameObject.transform().setRotation(-90);
        }
    }

    if (m_gameObject.id >= 0)
    {
        auto& ntmp = m_gameObject.transform().getGlobalPosition();
        min = { ntmp.z - 0.25f, ntmp.x - 0.25f };
        max = { min.x + 0.50f, min.y + 0.50f };
        std::cout << "Player update ------" << std::endl;
        std::cout << "current position: " << ntmp << std::endl;
        std::cout << "hitbox: min = " << min << " max = " << max;
        m_gameObject.scene().m_tree.update(m_gameObject.id, min, max, true);
        std::cout << "node position: min = " << m_gameObject.scene().m_tree.get_aabb(m_gameObject.id).min() << " max = " << m_gameObject.scene().m_tree.get_aabb(m_gameObject.id).max();
        std::cout << "----------" << std::endl;
    }

    if (sw::isKeyDown(m_keys[m_actions::BOMB])) {
        bomb();
    }
    updateAnimation();
    /*
    for (auto& it = *m_bombs.begin(); it != *m_bombs.end(); it++) {
    }
    */

    std::stringstream ss;
    ss << std::setprecision(2) << m_speed;

    m_bombtxt.value().setText(std::to_string(m_bombAvailable));
    m_speedtxt.value().setText(ss.str());
    m_rangetxt.value().setText(std::to_string(m_bombPower));
}

void moul::Player::increaseMaxBomb()
{
    m_bombNumberTotal += 1;
    m_bombAvailable += 1;
}

void moul::Player::increaseBombPower()
{
    m_bombPower += 1;
}

void moul::Player::increaseSpeed()
{
    m_speed += 1;
}

void moul::Player::addBomb()
{
    m_bombAvailable += 1;
}

void moul::Player::bomb()
{
    if (m_bombAvailable < 1)
        return;
    m_bombAvailable -= 1;
    auto& newBomb = m_gameObject.scene().createGameObject("Bomb_" + m_gameObject.name() + "_" + std::to_string(m_bombAvailable));
    auto& newBombCpt = newBomb.createComponent<moul::Bomb>("ScriptManager");
    newBombCpt.m_player.emplace(*this);
    newBombCpt.start();
    newBomb.transform().setPosition(((int)m_gameObject.transform().getGlobalPosition().x) + 0.5f, m_gameObject.transform().getGlobalPosition().y, ((int)m_gameObject.transform().getGlobalPosition().z) - 0.5f );
}

void moul::Player::die()
{
    m_gameObject.scene().eventManager.drop("PlayerDie");
}