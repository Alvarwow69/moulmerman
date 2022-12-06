/*
** ShipWreck Engine, 2022
** Player.cpp
*/

#include "Fire.hpp"
#include "Block.hpp"

moul::Fire::Fire(sw::GameObject& gameObject) :
sw::Component(gameObject),
m_spentTime(0.0f),
m_durationTime(1.5f)
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
}

void moul::Fire::update()
{
    double elapsedTime = sw::OpenGLModule::deltaTime();
    auto& trans = m_gameObject.transform().getGlobalPosition();
    auto size = sw::Vector2f{0.3f, 0.3f};

    std::array<std::byte, sizeof(size_t) * 256> buffer; // enough to fit in all nodes
    std::pmr::monotonic_buffer_resource mbr{buffer.data(), buffer.size()};
    std::pmr::polymorphic_allocator<int> pa{&mbr};
    std::pmr::list<int> list{pa};

    m_gameObject.scene().m_tree.query(m_gameObject.id, {trans.x - size.x, trans.z - size.y}, {trans.x + size.x, trans.z + size.y}, std::back_inserter(list));
    if (!list.empty()) {
        for (auto element : list) {
            auto* block = dynamic_cast<moul::Block*>(&m_gameObject.scene().m_lut[element].value());
            if (block)
                block->explode();
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