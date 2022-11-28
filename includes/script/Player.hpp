/*
** ShipWreck Engine, 2022
** Player.hpp
*/

#ifndef MOULERMAN_PLAYER_HPP
#define MOULERMAN_PLAYER_HPP

#include "components/Components.hpp"
#include "components/MeshRenderer.hpp"  
#include "components/BoxCollider.hpp"
#include "Bomb.hpp"
#include "SelectionPlayerType.hpp"
#include "utils/Inputs.hpp"
#include <memory>
#include "OpenGLModule.hpp"
#include "window/Window.hpp"
#include <map>

namespace moul
{
    class Player : public sw::Component
    {
        public:
            std::string m_modelName;
            sw::Vector2f m_modelPos;
            sw::Reference<sw::Text> m_bombtxt;
            sw::Reference<sw::Text> m_rangetxt;
            sw::Reference<sw::Text> m_speedtxt;

            void update();
            void start();
            bool isAlive();
            explicit Player(sw::GameObject& gameObject);
            void increaseMaxBomb();
            void increaseBombPower();
            void increaseSpeed();
            void addBomb();
        private:
            enum m_actions {
                FORWARD,
                BACKWARD,
                LEFT,
                RIGHT,
                BOMB
            };
            int m_bombPower = 1;
            int m_bombNumberTotal = 1;
            int m_bombAvailable = 1;
            float m_speed = 3.f;
            std::map<int, int> m_keys;
            bool m_alive = true;
            std::vector<std::shared_ptr<Bomb>> m_bombs;
            sw::Reference<SelectionPlayerType> m_type;
            sw::Reference<sw::MeshRenderer> m_mesh;
            sw::Reference<sw::ModelAnimator> m_animator;
            //sw::Reference<sw::BoxCollider> m_collider;
            void bomb();
            void setKeys();
            void die();
            void updateAnimation();
    };
}


#endif // MOULERMAN_PLAYER_HPP