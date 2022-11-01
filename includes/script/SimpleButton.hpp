/*
** ShipWreck Engine , 2022
** Button.hpp
*/

#ifndef MOULMERMAN_SMPLEBUTTON_HPP
#define MOULMERMAN_SMPLEBUTTON_HPP

#include "components/Components.hpp"
#include "script/SceneLoader.hpp"

namespace moul
{
    class SimpleButton : public sw::Component
    {
    public:
        std::string m_textureName;
        std::string m_buttonTitle;
        sw::Vector2f m_scale;
        sw::Vector3f m_position;
        sw::Vector3f m_txtPosition;
        void (*m_callback)(SimpleButton *);
        bool m_hover;

        explicit SimpleButton(sw::GameObject& gameObject);

    private:
        sw::Reference<sw::Sprite> m_sprite;
        sw::Reference<sw::Text> m_text;
        sw::Reference<sw::AudioSource> m_audio;
        void start();
        void update();
    }; // class Button
} // namespace moul

#endif //MOULMERMAN_SMPLEBUTTON_HPP
