/*
** ShipWreck Engine, 2022
** Bomb.hpp
*/

#ifndef MOULERMAN_BOMB_HPP
#define MOULERMAN_BOMB_HPP

#include "components/Components.hpp"
#include "components/MeshRenderer.hpp"  
#include "OpenGLModule.hpp"

namespace moul
{
    class Bomb : public sw::Component
    {
    public:
        std::string m_modelName;
        sw::Vector2f m_modelPos;
        void update();
        void start();
        void explode();
        bool hasExploded();
        void destroy();
        explicit Bomb(sw::GameObject& gameObject);
    private:
        bool m_hasExploded = false;
        float m_spentTime;
        int m_power;
        float m_explosionTime;
        float m_animTime;
        float m_lastTime;
        sw::Reference<sw::MeshRenderer> m_mesh;
        sw::Reference<sw::AudioSource> m_audio;
    };
}


#endif // MOULERMAN_BOMB_HPP