/*
** ShipWreck Engine , 2022
** Button.hpp
*/

#ifndef MOULMERMAN_BUTTON_HPP
#define MOULMERMAN_BUTTON_HPP

#include "components/Components.hpp"
#include "script/SceneLoader.hpp"

namespace moul
{
    class Button : public sw::Component
    {
    public:
        std::string m_textureName;
        sw::Vector3f m_position;
        std::string m_scene;

        Button(sw::GameObject& gameObject);

    private:
        sw::Reference<sw::Sprite> m_sprite;
        sw::Reference<inc::SceneLoader> m_loader;
        void start();
        void update();
    }; // class Button
} // namespace moul

#endif //MOULMERMAN_BUTTON_HPP
