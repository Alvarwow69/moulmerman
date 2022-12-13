/*
** ShipWreck Engine, 2022
** Player.cpp
*/

#include <iostream>

#include "Player.hpp"
#include "config/Config.hpp"
#include "GameManager.hpp"
#include "script/modifier/BombModifier.hpp"
#include "Fire.hpp"
#include "modifier/RangeModifier.hpp"
#include "modifier/SpeedModifier.hpp"
#include "Block.hpp"
#include "modifier/NinjaModifier.hpp"

#include <memory_resource> //magic trick

moul::Player::Player(sw::GameObject& gameObject) :
sw::Component(gameObject),
m_modelName("PLACEHOLDER"),
m_bombAvailable(1),
m_ninja(false)
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
    m_primitive.value().m_array[0].color = {1, 1, 0};
    m_primitive.value().m_array[1].color = {1, 1, 0};
    m_primitive.value().m_array[2].color = {1, 1, 0};
    m_primitive.value().m_array[3].color = {1, 1, 0};
    m_primitive.value().setActive(false);

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
    sw::Vector2f size = {0.2f, 0.2f};
    sw::Vector3f movement = {0, 0, 0};

    if (m_ninja) {
        m_ninjaTime += elapsedTime;
        if (m_ninjaTime >= 5) {
            m_ninja = false;
            m_gameObject.transform().setPosition(m_ninjaPos);
        }
    }

    
    std::vector<int> list;

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
            movement = {0, 0, m_speed * (float)elapsedTime};
        else if (list.size() != 0) {
            for (auto element : list) {
                auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_bomb = dynamic_cast<moul::BombModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_speed = dynamic_cast<moul::RangeModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_range = dynamic_cast<moul::SpeedModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_ninja = dynamic_cast<moul::NinjaModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* fire = dynamic_cast<moul::Fire*>(&m_gameObject.scene().m_lut[element].value());
                auto* block = dynamic_cast<moul::Block*>(&m_gameObject.scene().m_lut[element].value());
                if (m_ninja && block) {
                    movement = {0, 0, (float)(m_speed * elapsedTime * (block->m_destructible ? 1.0f : 0.0f))};
                    if (!block->m_destructible)
                        break;} else if ((bomb && !bomb->m_enable) || fire) {
                    movement = {0, 0, m_speed * (float)elapsedTime};
                } else if (bonus_bomb)
                    bonus_bomb->applyModifier(*this);
                else if (bonus_range)
                    bonus_range->applyModifier(*this);
                else if (bonus_speed)
                    bonus_speed->applyModifier(*this);
                else if (bonus_ninja)
                    bonus_ninja->applyModifier(*this);
            }
        }
        m_gameObject.transform().setRotation(0);
    }
    if (sw::isKeyDown(m_keys[m_actions::BACKWARD])) {
        min.y += -m_speed * elapsedTime;
        max.y += -m_speed * elapsedTime;
        m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
        if (!list.size())
            movement = {0, 0, -m_speed * (float)elapsedTime};
        else if (list.size() != 0) {
            for (auto element : list) {
                auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_bomb = dynamic_cast<moul::BombModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_speed = dynamic_cast<moul::RangeModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_range = dynamic_cast<moul::SpeedModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_ninja = dynamic_cast<moul::NinjaModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* fire = dynamic_cast<moul::Fire*>(&m_gameObject.scene().m_lut[element].value());
                auto* block = dynamic_cast<moul::Block*>(&m_gameObject.scene().m_lut[element].value());
                if (m_ninja && block) {
                    movement = {0, 0, (float)(-m_speed * elapsedTime * (block->m_destructible ? 1.0f : 0.0f))};
                    if (!block->m_destructible)
                        break;
                } else if ((bomb && !bomb->m_enable) || fire) {
                    movement = {0, 0, -m_speed * (float)elapsedTime};
                } else if (bonus_bomb)
                    bonus_bomb->applyModifier(*this);
                else if (bonus_range)
                    bonus_range->applyModifier(*this);
                else if (bonus_speed)
                    bonus_speed->applyModifier(*this);
                else if (bonus_ninja)
                    bonus_ninja->applyModifier(*this);
            }
        }
        m_gameObject.transform().setRotation(180);
    }
    if (sw::isKeyDown(m_keys[m_actions::LEFT])) {
        min.x += m_speed * elapsedTime;
        max.x += m_speed * elapsedTime;
        m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
        if (!list.size())
            movement = {m_speed * (float)elapsedTime, 0, 0};
        else if (list.size() != 0) {
            for (auto element : list) {
                auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_bomb = dynamic_cast<moul::BombModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_speed = dynamic_cast<moul::RangeModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_range = dynamic_cast<moul::SpeedModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_ninja = dynamic_cast<moul::NinjaModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* fire = dynamic_cast<moul::Fire*>(&m_gameObject.scene().m_lut[element].value());
                auto* block = dynamic_cast<moul::Block*>(&m_gameObject.scene().m_lut[element].value());
                if ((m_ninja && block)) {
                    movement = {(float)(m_speed * elapsedTime * (block->m_destructible ? 1.0f : 0.0f)), 0, 0};
                    if (!block->m_destructible)
                        break;} else if ((bomb && !bomb->m_enable) || fire) {
                    movement = {m_speed * (float)elapsedTime, 0, 0};
                }else if (bonus_bomb)
                    bonus_bomb->applyModifier(*this);
                else if (bonus_range)
                    bonus_range->applyModifier(*this);
                else if (bonus_speed)
                    bonus_speed->applyModifier(*this);
                else if (bonus_ninja)
                    bonus_ninja->applyModifier(*this);
            }
        }
        m_gameObject.transform().setRotation(90);
    }
    if (sw::isKeyDown(m_keys[m_actions::RIGHT])) {
        min.x += -m_speed * elapsedTime;
        max.x += -m_speed * elapsedTime;
        m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
        if (!list.size())
            movement = {-m_speed * (float)elapsedTime, 0, 0};
        else if (list.size() != 0) {
            for (auto element : list) {
                auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_bomb = dynamic_cast<moul::BombModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_speed = dynamic_cast<moul::RangeModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_range = dynamic_cast<moul::SpeedModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* bonus_ninja = dynamic_cast<moul::NinjaModifier*>(&m_gameObject.scene().m_lut[element].value());
                auto* fire = dynamic_cast<moul::Fire*>(&m_gameObject.scene().m_lut[element].value());
                auto* block = dynamic_cast<moul::Block*>(&m_gameObject.scene().m_lut[element].value());
                if ((m_ninja && block)) {
                    movement = {(float)(-m_speed * elapsedTime * (block->m_destructible ? 1.0f : 0.0f)), 0, 0};
                    if (!block->m_destructible)
                        break;} else if ((bomb && !bomb->m_enable) || fire) {
                    movement = {-m_speed * (float)elapsedTime, 0, 0};
                } else if (bonus_bomb)
                    bonus_bomb->applyModifier(*this);
                else if (bonus_range)
                    bonus_range->applyModifier(*this);
                else if (bonus_speed)
                    bonus_speed->applyModifier(*this);
                else if (bonus_ninja)
                    bonus_ninja->applyModifier(*this);
            }
        }
        m_gameObject.transform().setRotation(-90);
    }
    m_gameObject.transform().move(movement);

    if (sw::isKeyPressed(m_keys[m_actions::BOMB]))
        bomb();
    updateAnimation();

    if (m_gameObject.id >= 0)
    {
        auto& ntmp = m_gameObject.transform().getGlobalPosition();
        min = {ntmp.x - size.x, ntmp.z - size.x};
        max = {ntmp.x + size.y, ntmp.z + size.y};
        m_gameObject.scene().m_tree.update(m_gameObject.id, min, max, true);
    }

    std::stringstream ss;
    ss << std::setprecision(2) << m_speed;

    m_bombtxt.value().setText(std::to_string(m_bombAvailable));
    m_speedtxt.value().setText(ss.str());
    m_rangetxt.value().setText(std::to_string(m_bombPower));
}

void moul::Player::increaseMaxBomb(int neg)
{
    if (neg && m_bombNumberTotal > 1) {
        m_bombNumberTotal -= 1;
        m_bombAvailable = (m_bombAvailable >= m_bombNumberTotal ? m_bombAvailable - 1 : m_bombAvailable);
    } else if (!neg && m_bombNumberTotal < 10){
        m_bombNumberTotal += 1;
        m_bombAvailable += 1;
    }
}

void moul::Player::increaseBombPower(int neg)
{
    if (neg && m_bombPower > 1)
        m_bombPower -= 1;
    else if (!neg && m_bombPower < 5)
        m_bombPower += 1;
}

void moul::Player::increaseSpeed(int neg)
{
    if (neg && m_speed > 2)
        m_speed -= 1;
    else if (!neg && m_speed < 7)
        m_speed += 1;
}

void moul::Player::addBomb()
{
    if (m_bombAvailable < m_bombNumberTotal)
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
    newBombCpt.m_power = m_bombPower;
    newBombCpt.start();
}

void moul::Player::die()
{
    m_gameObject.setActive(false);
    m_gameObject.scene().m_lut.erase(m_gameObject.id);
    m_gameObject.scene().m_tree.erase(m_gameObject.id);
    sw::Config::GetConfig()["Setting"][m_gameObject.name()]["rank"] = std::to_string(moul::GameManager::GetPlayerLeft());
    m_gameObject.scene().eventManager.drop("PlayerDie");
}

void moul::Player::ninja()
{
    if (m_ninja)
        return;
    m_ninjaTime = 0.0;
    m_ninjaPos = m_gameObject.transform().getGlobalPosition();
    m_ninja = true;
}