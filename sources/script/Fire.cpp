/*
** ShipWreck Engine, 2022
** Player.cpp
*/

#include "Fire.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include "AI.hpp"
#include "modifier/BombModifier.hpp"
#include "modifier/SpeedModifier.hpp"
#include "modifier/RangeModifier.hpp"

moul::Fire::Fire(sw::GameObject& gameObject) :
sw::Component(gameObject),
m_spentTime(0.0f),
m_durationTime(1.0f)
{
    m_gameObject.scene().eventManager["Start"].subscribe(m_gameObject.name(), this, &moul::Fire::start);
    m_gameObject.scene().eventManager["Update"].subscribe(m_gameObject.name(), this, &moul::Fire::update);
}

moul::Fire::~Fire() noexcept
{
    m_gameObject.scene().eventManager["Start"].unsubscribe(m_gameObject.name());
    m_gameObject.scene().eventManager["Update"].unsubscribe(m_gameObject.name());
}

void moul::Fire::start()
{
    m_mesh.emplace(m_gameObject.createComponent<sw::MeshRenderer>("MeshRendererManager", "Fire"));

    auto& trans = m_gameObject.transform().getGlobalPosition();
    auto size = sw::Vector2f{0.3f, 0.3f};

    m_gameObject.scene().m_tree.insert(m_gameObject.id, {trans.x - size.x, trans.z - size.y}, {trans.x + size.x, trans.z + size.y});
    m_gameObject.scene().m_lut.emplace(m_gameObject.id, *this);

    m_primitive.emplace(m_gameObject.createComponent<sw::Primitive>("PrimitiveManager"));
    m_primitive.value().m_array[0].position = {trans.x + -0.025f, trans.y + 1.2f, trans.z + -0.025f};
    m_primitive.value().m_array[1].position = {trans.x + 0.025f, trans.y + 1.2f, trans.z + -0.025f};
    m_primitive.value().m_array[2].position = {trans.x + 0.025f, trans.y + 1.2f, trans.z + 0.025f};
    m_primitive.value().m_array[3].position = {trans.x + -0.025f, trans.y + 1.2f, trans.z + 0.025f};
    m_primitive.value().m_array[0].color = {1, 0, 0};
    m_primitive.value().m_array[1].color = {1, 0, 0};
    m_primitive.value().m_array[2].color = {1, 0, 0};
    m_primitive.value().m_array[3].color = {1, 0, 0};
    m_primitive.value().setActive(false);
}

void moul::Fire::update()
{
    double elapsedTime = sw::OpenGLModule::deltaTime();
    auto& trans = m_gameObject.transform().getGlobalPosition();
    auto size = sw::Vector2f{0.3f, 0.3f};

    /*
    std::array<std::byte, sizeof(size_t) * 256> buffer; // enough to fit in all nodes
    std::pmr::monotonic_buffer_resource mbr{buffer.data(), buffer.size()};
    std::pmr::polymorphic_allocator<int> pa{&mbr};
    std::pmr::list<int> list{pa};
    */
    std::vector<int> list;

    m_gameObject.scene().m_tree.query(m_gameObject.id, {trans.x - size.x, trans.z - size.y}, {trans.x + size.x, trans.z + size.y}, std::back_inserter(list));
    if (list.size()) {
        for (auto element : list) {
            auto* block = dynamic_cast<moul::Block*>(&m_gameObject.scene().m_lut[element].value());
            auto* player = dynamic_cast<moul::Player*>(&m_gameObject.scene().m_lut[element].value());
            auto* ai = dynamic_cast<moul::AI*>(&m_gameObject.scene().m_lut[element].value());
            auto* bomb = dynamic_cast<moul::BombModifier*>(&m_gameObject.scene().m_lut[element].value());
            auto* range = dynamic_cast<moul::SpeedModifier*>(&m_gameObject.scene().m_lut[element].value());
            auto* speed = dynamic_cast<moul::RangeModifier*>(&m_gameObject.scene().m_lut[element].value());
            if (block)
                block->explode();
            if (player)
                player->die();
            if (bomb)
                bomb->destroy(m_gameObject.id);
            else if (range)
                range->destroy(m_gameObject.id);
            else if (speed)
                speed->destroy(m_gameObject.id);
            else if (ai)
                ai->die();
        }

    }

    m_spentTime += elapsedTime;
    if (m_spentTime > m_durationTime && m_gameObject.isActive()) {
        m_gameObject.setActive(false);
        m_gameObject.scene().m_tree.erase(m_gameObject.id);
        m_gameObject.scene().m_lut.erase(m_gameObject.id);
        m_gameObject.scene().deleteGameObject(m_gameObject.name());
    }
}