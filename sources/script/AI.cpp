
#include <iostream>

#include "AI.hpp"
#include "config/Config.hpp"
#include "GameManager.hpp"
#include "script/modifier/BombModifier.hpp"
#include "Fire.hpp"
#include "modifier/RangeModifier.hpp"
#include "modifier/SpeedModifier.hpp"
#include "Block.hpp"
#include "Bomb.hpp"
#include "Player.hpp"
#include "modifier/NinjaModifier.hpp"
#include <chrono>
#include <random>

#include <cstdlib>
#include <ctime>

moul::AI::AI(sw::GameObject& gameObject) :
    sw::Component(gameObject),
    m_modelName("PLACEHOLDER"),
    m_bombAvailable(1),
    m_ninja(false),
    selected(NONE),
    acting(false),
    previous(NONE)
{
    std::srand(std::time(nullptr));
    m_gameObject.scene().eventManager["Update"].subscribe(m_gameObject.name(), this, &moul::AI::update);
}

bool moul::AI::isAlive()
{
    return m_alive;
}

void moul::AI::start()
{
    m_mesh.emplace(m_gameObject.createComponent<sw::MeshRenderer>("MeshRendererManager", m_modelName));
    m_animator.emplace(m_gameObject.createComponent<sw::ModelAnimator>("ModelAnimatorManager", "Player_idle"));
    m_animator.value().attachModel(m_modelName);
    m_mesh.value().m_animator.emplace(m_animator.value());

    m_primitive.emplace(m_gameObject.createComponent<sw::Primitive>("PrimitiveManager"));
    m_primitive.value().m_array[0].color = { 1, 1, 0 };
    m_primitive.value().m_array[1].color = { 1, 1, 0 };
    m_primitive.value().m_array[2].color = { 1, 1, 0 };
    m_primitive.value().m_array[3].color = { 1, 1, 0 };
    m_primitive.value().setActive(false);

    m_alive = true;
    m_speed = 3.f;
    std::stringstream ss;
    ss << std::setprecision(2) << m_speed;
    m_bombtxt.value().setText(std::to_string(m_bombAvailable));
    m_speedtxt.value().setText(ss.str());
    m_rangetxt.value().setText(std::to_string(m_bombPower));
}

void moul::AI::updateAnimation()
{
    if (selected == BOMB || selected == NONE)
        m_animator.value().playAnimation("Player_idle");
    else    
        m_animator.value().playAnimation("Player_walk");
}

moul::AI::m_actions moul::AI::find_free_path(const sw::Vector2f &min, const sw::Vector2f &max, const float &elapsedTime, const moul::AI::m_actions forced_path)
{
    std::vector<int> list;
    sw::Vector2f min_check[4] = { {min.x, min.y + (float)m_speed * elapsedTime}, {min.x, min.y + (float)-m_speed * elapsedTime}, {min.x + (float)m_speed * elapsedTime, min.y}, {min.x + (float)-m_speed * elapsedTime, min.y} };
    sw::Vector2f max_check[4] = { {max.x, max.y + (float)m_speed * elapsedTime}, {max.x, max.y + (float)-m_speed * elapsedTime}, {max.x + (float)m_speed * elapsedTime, max.y}, {max.x + -m_speed * elapsedTime, max.y} };

    int free_count = 0;
    m_actions res = NONE;
    m_actions bomb_check = NONE;

    std::vector<m_actions> path;
    if (forced_path == NONE)
    {
        for (int i = 0; i < 4; i++)
        {
            m_gameObject.scene().m_tree.query(m_gameObject.id, min_check[i], max_check[i], std::back_inserter(list));
            if (!list.size())
                path.push_back((m_actions)i);
            else {
                for (auto element : list)
                {
                    auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                    auto* block = dynamic_cast<moul::Block*>(&m_gameObject.scene().m_lut[element].value());
                    auto* player = dynamic_cast<moul::Player*>(&m_gameObject.scene().m_lut[element].value());

                    if (block) {
                        if (!block->m_destructible)
                            break;
                        if (m_ninja)
                            path.push_back((m_actions)i);
                        else
                            continue;
                    }
                    else if ((bomb && !bomb->m_enable))
                    {
                        auto act = find_free_path(min_check[i], max_check[i], elapsedTime, (m_actions)i);
                        if (act != NONE)
                            path.push_back(act);
                    }
                    else if (!player && !block && !bomb)
                        path.push_back((m_actions)i);
                }
            }
        }
    } else
    {
        switch (forced_path)
        {
        case FORWARD:
        {
            sw::Vector2f minc{ min.x, min.y + (float)m_speed * elapsedTime };
            sw::Vector2f maxc{ max.x, max.y + (float)m_speed * elapsedTime };
            m_gameObject.scene().m_tree.query(m_gameObject.id, minc, maxc, std::back_inserter(list));
            if (!list.size())
                path.push_back(FORWARD);
            else {
                for (auto element : list)
                {
                    auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                    auto* block = dynamic_cast<moul::Block*>(&m_gameObject.scene().m_lut[element].value());
                    auto* player = dynamic_cast<moul::Player*>(&m_gameObject.scene().m_lut[element].value());

                    if (block) {
                        if (!block->m_destructible)
                            break;
                        if (m_ninja)
                            path.push_back(FORWARD);
                        else
                            continue;
                    }
                    else if ((bomb && !bomb->m_enable))
                    {
                        auto act = find_free_path(minc, maxc, elapsedTime, FORWARD);
                        if (act != NONE)
                            path.push_back(act);
                    }
                    else if (!player && !block && !bomb)
                        path.push_back(FORWARD);
                }
            }
            break;
        }
        case BACKWARD:
        {
            sw::Vector2f minc{ min.x, min.y + (float)-m_speed * elapsedTime };
            sw::Vector2f maxc{ max.x, max.y + (float)-m_speed * elapsedTime };
            m_gameObject.scene().m_tree.query(m_gameObject.id, minc, maxc, std::back_inserter(list));
            if (!list.size())
                path.push_back(BACKWARD);
            else {
                for (auto element : list)
                {
                    auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                    auto* block = dynamic_cast<moul::Block*>(&m_gameObject.scene().m_lut[element].value());
                    auto* player = dynamic_cast<moul::Player*>(&m_gameObject.scene().m_lut[element].value());

                    if (block) {
                        if (!block->m_destructible)
                            break;
                        if (m_ninja)
                            path.push_back(BACKWARD);
                        else
                            continue;
                    }
                    else if ((bomb && !bomb->m_enable))
                    {
                        auto act = find_free_path(minc, maxc, elapsedTime, BACKWARD);
                        if (act != NONE)
                            path.push_back(act);
                    }
                    else if (!player && !block && !bomb)
                        path.push_back(BACKWARD);
                }
            }
            break;
        }
        case LEFT:
        {
            sw::Vector2f minc{ min.x + (float)m_speed * elapsedTime, min.y };
            sw::Vector2f maxc{ max.x + (float)m_speed * elapsedTime, max.y };
            m_gameObject.scene().m_tree.query(m_gameObject.id, minc, maxc, std::back_inserter(list));
            if (!list.size())
                path.push_back(LEFT);
            else {
                for (auto element : list)
                {
                    auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                    auto* block = dynamic_cast<moul::Block*>(&m_gameObject.scene().m_lut[element].value());
                    auto* player = dynamic_cast<moul::Player*>(&m_gameObject.scene().m_lut[element].value());

                    if (block) {
                        if (!block->m_destructible)
                            continue;
                        if (m_ninja)
                            path.push_back(LEFT);
                        else
                            continue;
                    }
                    else if ((bomb && !bomb->m_enable))
                    {
                        auto act = find_free_path(minc, maxc, elapsedTime, LEFT);
                        if (act != NONE)
                            path.push_back(act);
                    }
                    else if (!player && !block && !bomb)
                        path.push_back(LEFT);
                }
            }
            break;
        }
        case RIGHT:
        {
            sw::Vector2f minc{ min.x + (float)-m_speed * elapsedTime, min.y };
            sw::Vector2f maxc{ max.x + -m_speed * elapsedTime, max.y };
            m_gameObject.scene().m_tree.query(m_gameObject.id, minc, maxc, std::back_inserter(list));
            if (!list.size())
                path.push_back(RIGHT);
            else {
                for (auto element : list)
                {
                    auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                    auto* block = dynamic_cast<moul::Block*>(&m_gameObject.scene().m_lut[element].value());
                    auto* player = dynamic_cast<moul::Player*>(&m_gameObject.scene().m_lut[element].value());

                    if (block) {
                        if (!block->m_destructible)
                            break;
                        if (m_ninja)
                            path.push_back(RIGHT);
                        else
                            continue;
                    }
                    else if ((bomb && !bomb->m_enable))
                    {
                        auto act = find_free_path(minc, maxc, elapsedTime, RIGHT);
                        if (act != NONE)
                            path.push_back(act);
                    }
                    else if (!player && !block && !bomb)
                        path.push_back(RIGHT);
                }
            }
            break;
        }
        default: path.push_back(NONE);
            break;
        }
    }
    if (path.empty())
        return NONE;
    auto iter = std::rand() % path.size();
    return path.at(iter);
}

void moul::AI::update()
{
    using namespace std::chrono_literals;
    if (moul::GameManager::GetGameState() != moul::GameManager::INGAME)
        return;
    float elapsedTime = sw::OpenGLModule::deltaTime();
    sw::Vector2f size = { 0.2f, 0.2f };
    sw::Vector3f movement = { 0, 0, 0 };

    if (m_ninja) {
        m_ninjaTime += elapsedTime;
        if (m_ninjaTime >= 5) {
            m_ninja = false;
            m_gameObject.transform().setPosition(m_ninjaPos);
        }
    }


    std::vector<int> list;

    auto& tmp = m_gameObject.transform().getGlobalPosition();
    sw::Vector2f min{ tmp.x - size.x, tmp.z - size.x };
    sw::Vector2f max{ tmp.x + size.y, tmp.z + size.y };
    int path = -1;

    if (!acting)
    {
        bool bombing = false;
        std::array<int, 4> priorities;
        int choice = 0;
        sw::Vector2f min_check[4] = { {min.x, min.y + (float)m_speed * elapsedTime}, {min.x, min.y + (float)-m_speed * elapsedTime}, {min.x + (float)m_speed * elapsedTime, min.y}, {min.x + (float)-m_speed * elapsedTime, min.y} };
        sw::Vector2f max_check[4] = { {max.x, max.y + (float)m_speed * elapsedTime}, {max.x, max.y + (float)-m_speed * elapsedTime}, {max.x + (float)m_speed * elapsedTime, max.y}, {max.x + -m_speed * elapsedTime, max.y} };

        std::vector<m_actions> paths;
        paths.reserve(4);

        for (int i = 0; i < 4; i++)
        {
            int priority = 0;
            m_gameObject.scene().m_tree.query(m_gameObject.id, min_check[i], max_check[i], std::back_inserter(list));
            if (!list.size())
            {
                priority = 0;
            }
            else if (list.size() != 0) {
                for (auto element : list) {
                    auto* bomb = dynamic_cast<moul::Bomb*>(&m_gameObject.scene().m_lut[element].value());
                    auto* bonus_bomb = dynamic_cast<moul::BombModifier*>(&m_gameObject.scene().m_lut[element].value());
                    auto* bonus_speed = dynamic_cast<moul::RangeModifier*>(&m_gameObject.scene().m_lut[element].value());
                    auto* bonus_range = dynamic_cast<moul::SpeedModifier*>(&m_gameObject.scene().m_lut[element].value());
                    auto* bonus_ninja = dynamic_cast<moul::NinjaModifier*>(&m_gameObject.scene().m_lut[element].value());
                    auto* fire = dynamic_cast<moul::Fire*>(&m_gameObject.scene().m_lut[element].value());
                    auto* block = dynamic_cast<moul::Block*>(&m_gameObject.scene().m_lut[element].value());
                    auto* player = dynamic_cast<moul::Player*>(&m_gameObject.scene().m_lut[element].value());

                    if (block) {
                        if (!block->m_destructible)
                        {
                            priority = -1;
                            break;
                        }
                        else
                        {
                            priority = 3;
                            bombing = true;
                        }
                    }
                    else if (bomb || fire) {
                        priority = -1;
                    }
                    else if (bonus_bomb || bonus_range || bonus_speed || bonus_ninja)
                        priority = 2;
                    else if (player)
                    {
                        bombing = true;
                        priority = 4;
                    }
                }
            }
            list.clear();
            priorities[i] = priority;
            if (priority > path)
            {
                path = priority;
                selected = (m_actions)i;
                previous = selected;
            }
            if (priority >= 0)
                paths.push_back((m_actions)i);
        }
        start_time = std::chrono::high_resolution_clock::now();
        if (path >= 3)
            selected = BOMB;
        else if (!paths.empty())
        {
            selected = paths.at(std::rand() % paths.size());
        }
        else
            selected = NONE;
        acting = true;
    }
    else {

        m_primitive.value().m_array[0].position = { min.x, tmp.y + 1.1f, min.y };
        m_primitive.value().m_array[1].position = { max.x, tmp.y + 1.1f, min.y };
        m_primitive.value().m_array[2].position = { max.x, tmp.y + 1.1f, max.y };
        m_primitive.value().m_array[3].position = { min.x, tmp.y + 1.1f, max.y };

        if (selected == BOMB)
        {
            bomb();
            selected = find_free_path(min, max, elapsedTime * 5);
        }

            if (selected == FORWARD) {
                min.y += m_speed * elapsedTime;
                max.y += m_speed * elapsedTime;
                m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
                if (!list.size())
                    movement = { 0, 0, m_speed * (float)elapsedTime };
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
                            movement = { 0, 0, (float)(m_speed * elapsedTime * (block->m_destructible ? 1.0f : 0.0f)) };
                            if (!block->m_destructible)
                                break;
                        }
                        else if ((bomb && !bomb->m_enable) || fire) {
                            movement = { 0, 0, m_speed * (float)elapsedTime };
                        }
                        else if (bonus_bomb)
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
            if (selected == BACKWARD) {
                min.y += -m_speed * elapsedTime;
                max.y += -m_speed * elapsedTime;
                m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
                if (!list.size())
                    movement = { 0, 0, -m_speed * (float)elapsedTime };
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
                            movement = { 0, 0, (float)(-m_speed * elapsedTime * (block->m_destructible ? 1.0f : 0.0f)) };
                            if (!block->m_destructible)
                                break;
                        }
                        else if ((bomb && !bomb->m_enable) || fire) {
                            movement = { 0, 0, -m_speed * (float)elapsedTime };
                        }
                        else if (bonus_bomb)
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
            if (selected == LEFT) {
                min.x += m_speed * elapsedTime;
                max.x += m_speed * elapsedTime;
                m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
                if (!list.size())
                    movement = { m_speed * (float)elapsedTime, 0, 0 };
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
                            movement = { (float)(m_speed * elapsedTime * (block->m_destructible ? 1.0f : 0.0f)), 0, 0 };
                            if (!block->m_destructible)
                                break;
                        }
                        else if ((bomb && !bomb->m_enable) || fire) {
                            movement = { m_speed * (float)elapsedTime, 0, 0 };
                        }
                        else if (bonus_bomb)
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
            if (selected == RIGHT) {
                min.x += -m_speed * elapsedTime;
                max.x += -m_speed * elapsedTime;
                m_gameObject.scene().m_tree.query(m_gameObject.id, min, max, std::back_inserter(list));
                if (!list.size())
                    movement = { -m_speed * (float)elapsedTime, 0, 0 };
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
                            movement = { (float)(-m_speed * elapsedTime * (block->m_destructible ? 1.0f : 0.0f)), 0, 0 };
                            if (!block->m_destructible)
                                break;
                        }
                        else if ((bomb && !bomb->m_enable) || fire) {
                            movement = { -m_speed * (float)elapsedTime, 0, 0 };
                        }
                        else if (bonus_bomb)
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
            auto end = std::chrono::high_resolution_clock::now();
            if (end - start_time >= 800ms)
                acting = false;
    }
    m_gameObject.transform().move(movement);
    updateAnimation();

    if (m_gameObject.id >= 0)
    {
        auto& ntmp = m_gameObject.transform().getGlobalPosition();
        min = { ntmp.x - size.x, ntmp.z - size.x };
        max = { ntmp.x + size.y, ntmp.z + size.y };
        m_gameObject.scene().m_tree.update(m_gameObject.id, min, max, true);
    }

    std::stringstream ss;
    ss << std::setprecision(2) << m_speed;

    m_bombtxt.value().setText(std::to_string(m_bombAvailable));
    m_speedtxt.value().setText(ss.str());
    m_rangetxt.value().setText(std::to_string(m_bombPower));
}

void moul::AI::increaseMaxBomb(int neg)
{
    if (neg && m_bombNumberTotal > 1) {
        m_bombNumberTotal -= 1;
        m_bombAvailable = (m_bombAvailable >= m_bombNumberTotal ? m_bombAvailable - 1 : m_bombAvailable);
    }
    else if (!neg && m_bombNumberTotal < 10) {
        m_bombNumberTotal += 1;
        m_bombAvailable += 1;
    }
}

void moul::AI::increaseBombPower(int neg)
{
    if (neg && m_bombPower > 1)
        m_bombPower -= 1;
    else if (!neg && m_bombPower < 5)
        m_bombPower += 1;
}

void moul::AI::increaseSpeed(int neg)
{
    if (neg && m_speed > 2)
        m_speed -= 1;
    else if (!neg && m_speed < 7)
        m_speed += 1;
}

void moul::AI::addBomb()
{
    if (m_bombAvailable < m_bombNumberTotal)
        m_bombAvailable += 1;
}

void moul::AI::bomb()
{
    if (m_bombAvailable < 1)
        return;
    m_bombAvailable -= 1;
    auto& newBomb = m_gameObject.scene().createGameObject("Bomb_" + m_gameObject.name() + "_" + std::to_string(m_bombAvailable) + std::to_string(sw::OpenGLModule::chrono().getTotalTime()));
    auto& newBombCpt = newBomb.createComponent<moul::Bomb>("ScriptManager");
    newBombCpt.m_ai.emplace(*this);
    newBombCpt.ai_owned = true;
    newBomb.transform().setPosition(((int)m_gameObject.transform().getGlobalPosition().x) + 0.5f, m_gameObject.transform().getGlobalPosition().y, ((int)m_gameObject.transform().getGlobalPosition().z) - 0.5f);
    newBombCpt.m_power = m_bombPower;
    newBombCpt.start();
}

void moul::AI::die()
{
    m_gameObject.setActive(false);
    m_gameObject.scene().m_lut.erase(m_gameObject.id);
    m_gameObject.scene().m_tree.erase(m_gameObject.id);
    sw::Config::GetConfig()["Setting"][m_gameObject.name()]["rank"] = std::to_string(moul::GameManager::GetPlayerLeft());
    m_gameObject.scene().eventManager.drop("PlayerDie");
}

void moul::AI::ninja()
{
    if (m_ninja)
        return;
    m_ninjaTime = 0.0;
    m_ninjaPos = m_gameObject.transform().getGlobalPosition();
    m_ninja = true;
}