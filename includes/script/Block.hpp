/*
** ShipWreck Engine, 2022
** Block.hpp
*/

#ifndef MOULERMAN_BLOCK_HPP
#define MOULERMAN_BLOCK_HPP

#include "components/Components.hpp"
#include "OpenGLModule.hpp"

namespace moul
{
    class Block : public sw::Component
    {
    public:
        void start();
        void explode();
        explicit Block(sw::GameObject& gameObject);
        ~Block() override;
        std::string m_modelName;
        sw::Vector2f m_pos;
        bool m_destructible;
    private:
        sw::Reference<sw::MeshRenderer> m_mesh;

        void createBomb();
        void createRange();
        void createSpeed();
        void createNinja();
        sw::Reference<sw::Primitive> m_primitive;
    }; // class Block
} // namespace moul


#endif // MOULERMAN_BLOCK_HPP