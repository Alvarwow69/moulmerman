#pragma once

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
#include <chrono>

namespace moul
{
    class Bomb;

    class AI : public sw::Component
    {
        public:
            std::string m_modelName;
            std::string m_name;
            sw::Vector2f m_modelPos;
            sw::Reference<sw::Text> m_bombtxt;
            sw::Reference<sw::Text> m_rangetxt;
            sw::Reference<sw::Text> m_speedtxt;

            void update();
            void start();
            bool isAlive();
            explicit AI(sw::GameObject& gameObject);
            void increaseMaxBomb(int neg = 0);
            void increaseBombPower(int neg = 0);
            void increaseSpeed(int neg = 0);
            void addBomb();
            void die();
            void ninja();
    private:
            enum m_actions {
                FORWARD = 0,
                BACKWARD,
                LEFT,
                RIGHT,
                BOMB,
                NONE = -1
            };
            int m_bombPower = 1;
            int m_bombNumberTotal = 1;
            int m_bombAvailable = 1;
            m_actions selected;
            m_actions previous;
            float m_speed = 3.f;
            bool m_alive = true;
            std::vector<std::shared_ptr<Bomb>> m_bombs;
            sw::Reference<SelectionPlayerType> m_type;
            sw::Reference<sw::MeshRenderer> m_mesh;
            sw::Reference<sw::ModelAnimator> m_animator;
            sw::Reference<sw::Primitive> m_primitive;
            double m_ninjaTime;
            sw::Vector3f m_ninjaPos;
            bool m_ninja;
            decltype(std::chrono::high_resolution_clock::now()) start_time;
            bool acting;
            void bomb();
            void updateAnimation();

            m_actions find_free_path(const sw::Vector2f& min, const sw::Vector2f& max, const float &elapsedTime, const m_actions forced_path = NONE);
    };
}
