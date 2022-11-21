/*
** ShipWreck Engine, 2022
** Bomb.hpp
*/

#ifndef MOULERMAN_FIRE_HPP
#define MOULERMAN_FIRE_HPP

#include "components/Components.hpp"
#include "components/MeshRenderer.hpp"  
#include "OpenGLModule.hpp"

namespace moul
{
    class Fire : public sw::Component
    {
    public:
        void update();
        void start();
        explicit Fire(sw::GameObject& gameObject);
        ~Fire() override;
    private:
        float m_spentTime;
        float m_durationTime;
        sw::Reference<sw::MeshRenderer> m_mesh;
    }; // class Fire
} // namespace moul


#endif // MOULERMAN_FIRE_HPP