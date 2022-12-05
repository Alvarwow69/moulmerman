/*
** ShipWreck Engine, 2022
** Player.cpp
*/

#include <iostream>

#include "Player.hpp"
#include "config/Config.hpp"
#include "GameManager.hpp"
#include "script/modifier/BombModifier.hpp"

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

    m_primitive.emplace(m_gameObject.createComponent<sw::Primitive>("PrimitiveManager"));
    m_primitive.value().m_array[0].position = {-0.025f, 0.2f, -0.025f};
    m_primitive.value().m_array[1].position = {0.025f, 0.2f, -0.025f};
    m_primitive.value().m_array[2].position = {0.025f, 0.2f, 0.025f};
    m_primitive.value().m_array[3].position = {-0.025f, 0.2f, 0.025f};
    m_primitive.value().m_array[0].color = {1, 1, 0};
    m_primitive.value().m_array[1].color = {1, 1, 0};
    m_primitive.value().m_array[2].color = {1, 1, 0};
    m_primitive.value().m_array[3].color = {1, 1, 0};

    m_alive = true;
    m_speed = 3.f;
    //m_collider.emplace(m_gameObject.createComponent<sw::BoxCollider>("BoxColliderManager"));
    //m_collider.value().setSize(1.0f, 1.0f);
    setKeys();
    std::stringstream ss;
    ss << std::setprecision(2) << m_speed;
    m_bombtxt.value().setText(std::to_string(m_bombAvailable));
    m_speedtxt.value().setText(ss.str());
    m_rangetxt.value().setText(std::to_string(m_bombPower));
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
    if (moul::GameManager::GetGameState() != moul::GameManager::INGAME)
        return;
    double elapsedTime = sw::OpenGLModule::deltaTime();
    sw::Vector2f size = {0.3f, 0.3f};
    
    std::array<std::byte, sizeof(size_t) * 256> buffer; // enough to fit in all nodes
    std::pmr::monotonic_buffer_resource mbr{buffer.data(), buffer.size()};
    std::pmr::polymorphic_allocator<int> pa{&mbr};
    std::pmr::list<int> list{pa};

    //std::vector<int> candidates;
    auto &tmp = m_gameObject.transform().getGlobalPosition();
    sw::Vector2f min{tmp.x - size.x, tmp.z - size.x};
    sw::Vector2f max{tmp.x + size.y, tmp.z + size.y};

    m_primitive.value().m_array[0].position = {min.x, tmp.y + 1.1f, min.y};
    m_primitive.value().m_array[1].position = {max.x, tmp.y + 1.1f, min.y};
    m_primitive.value().m_array[2].position = {max.x, tmp.y + 1.1f, max.y};
    m_primitive.value().m_array[3].position = {min.x, tmp.y + 1.1f, max.y};

    if (sw::isKeyDown(m_keys[m_actions::FORWARD])) {
        min.y += m_speed * elapsedTime;
        max.y += m_speed * elapsedTime;
        m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
        if (!list.size())
            m_gameObject.transform().move(0, 0, m_speed * elapsedTime);
        else if (list.size() == 1) {
            for (auto element : list) {
                auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus = dynamic_cast<moul::BombModifier*>(&m_gameObject.scene().m_lut[element].value());
                if (bomb && !bomb->m_enable)
                    m_gameObject.transform().move(0, 0, m_speed * elapsedTime);
                else if (bonus)
                    bonus->applyModifier(*this);
            }
        }
        m_gameObject.transform().setRotation(0);
    } else if (sw::isKeyDown(m_keys[m_actions::BACKWARD])) {
        min.y += -m_speed * elapsedTime;
        max.y += -m_speed * elapsedTime;
        m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
        if (!list.size())
            m_gameObject.transform().move(0, 0, -m_speed * elapsedTime);
        else if (list.size() == 1) {
            for (auto element : list) {
                auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus = dynamic_cast<moul::BombModifier*>(&m_gameObject.scene().m_lut[element].value());
                if (bomb && !bomb->m_enable)
                    m_gameObject.transform().move(0, 0, -m_speed * elapsedTime);
                else if (bonus)
                    bonus->applyModifier(*this);
            }
        }
        m_gameObject.transform().setRotation(180);
    } else if (sw::isKeyDown(m_keys[m_actions::LEFT])) {
        min.x += m_speed * elapsedTime;
        max.x += m_speed * elapsedTime;
        m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
        if (!list.size())
            m_gameObject.transform().move(m_speed * elapsedTime, 0, 0);
        else if (list.size() == 1) {
            for (auto element : list) {
                auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus = dynamic_cast<moul::BombModifier*>(&m_gameObject.scene().m_lut[element].value());
                if (bomb && !bomb->m_enable)
                    m_gameObject.transform().move(m_speed * elapsedTime, 0, 0);
                else if (bonus)
                    bonus->applyModifier(*this);
            }
        }
        m_gameObject.transform().setRotation(90);
    } else if (sw::isKeyDown(m_keys[m_actions::RIGHT])) {
        min.x += -m_speed * elapsedTime;
        max.x += -m_speed * elapsedTime;
        m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
        if (!list.size())
            m_gameObject.transform().move(-m_speed * elapsedTime, 0, 0);
        else if (list.size() == 1) {
            for (auto element : list) {
                auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus = dynamic_cast<moul::BombModifier*>(&m_gameObject.scene().m_lut[element].value());
                if (bomb && !bomb->m_enable)
                    m_gameObject.transform().move(-m_speed * elapsedTime, 0, 0);
                else if (bonus)
                    bonus->applyModifier(*this);
            }
        }
        m_gameObject.transform().setRotation(-90);
    }

    if (sw::isKeyPressed(m_keys[m_actions::BOMB]))
        bomb();
    updateAnimation();

    std::stringstream ss;
    ss << std::setprecision(2) << m_speed;

    m_bombtxt.value().setText(std::to_string(m_bombAvailable));
    m_speedtxt.value().setText(ss.str());
    m_rangetxt.value().setText(std::to_string(m_bombPower));
}

void moul::Player::increaseMaxBomb(int neg)
{
    if (neg) {
        m_bombNumberTotal -= 1;
        m_bombAvailable = (m_bombAvailable == m_bombNumberTotal ? m_bombAvailable - 1 : m_bombAvailable);
    } else {
        m_bombNumberTotal += 1;
        m_bombAvailable += 1;
    }
}

void moul::Player::increaseBombPower(int neg)
{
    if (neg)
        m_bombPower -= 1;
    else
        m_bombPower += 1;
}

void moul::Player::increaseSpeed(int neg)
{
    if (neg)
        m_speed -= 1;
    else
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
    auto& newBomb = m_gameObject.scene().createGameObject("Bomb_" + m_gameObject.name() + "_" + std::to_string(m_bombAvailable) + std::to_string(sw::OpenGLModule::chrono().getTotalTime()));
    auto& newBombCpt = newBomb.createComponent<moul::Bomb>("ScriptManager");
    newBombCpt.m_player.emplace(*this);
    newBomb.transform().setPosition(((int)m_gameObject.transform().getGlobalPosition().x) + 0.5f, m_gameObject.transform().getGlobalPosition().y, ((int)m_gameObject.transform().getGlobalPosition().z) - 0.5f );
    newBombCpt.start();
}

void moul::Player::die()
{
    m_gameObject.scene().eventManager.drop("PlayerDie");
}