/*
** ShipWreck Engine, 2022
** Block.cpp
*/

#include "Block.hpp"

moul::Block::Block(sw::GameObject& gameObject) :
sw::Component(gameObject),
m_modelName()
{
    m_gameObject.scene().eventManager["Start"].subscribe(m_gameObject.name(), this, &moul::Block::start);
}

moul::Block::~Block() noexcept
{
}

void moul::Block::start()
{
    auto& trans = m_gameObject.transform();
    m_mesh.emplace(m_gameObject.createComponent<sw::MeshRenderer>("MeshRendererManager", m_modelName));
    m_primitive.emplace(m_gameObject.createComponent<sw::Primitive>("PrimitiveManager"));
    m_primitive.value().m_array[0].position = {trans.getGlobalPosition().x + 0.0f, trans.getGlobalPosition().y + 1.1f, trans.getGlobalPosition().z + 0.0f};
    m_primitive.value().m_array[1].position = {trans.getGlobalPosition().x + 1.0f, trans.getGlobalPosition().y + 1.1f, trans.getGlobalPosition().z + 0.0f};
    m_primitive.value().m_array[2].position = {trans.getGlobalPosition().x + 1.0f, trans.getGlobalPosition().y + 1.1f, trans.getGlobalPosition().z + -1.0f};
    m_primitive.value().m_array[3].position = {trans.getGlobalPosition().x + 0.0f, trans.getGlobalPosition().y + 1.1f, trans.getGlobalPosition().z + -1.0f};
    m_primitive.value().m_array[0].color = {0, 0, 1};
    m_primitive.value().m_array[1].color = {0, 0, 1};
    m_primitive.value().m_array[2].color = {0, 0, 1};
    m_primitive.value().m_array[3].color = {0, 0, 1};
}

void moul::Block::explode()
{
    m_gameObject.setActive(false);
    m_gameObject.scene().m_tree.erase(m_gameObject.id);
    if (std::rand() % 100 <= 5)
        std::cout << "Bonus" << std::endl;
}