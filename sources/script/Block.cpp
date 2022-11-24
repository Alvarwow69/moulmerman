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
    m_mesh.emplace(m_gameObject.createComponent<sw::MeshRenderer>("MeshRendererManager", m_modelName));
}

void moul::Block::explode()
{
    m_gameObject.setActive(false);
    if (std::rand() % 100 <= 5)
        std::cout << "Bonus" << std::endl;
}