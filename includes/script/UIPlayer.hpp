/*
** ShipWreck Engine, 2022
** UI_Player.hpp
*/

#ifndef MOULERMAN_UIPLAYER_HPP
#define MOULERMAN_UIPLAYER_HPP

#include "components/Components.hpp"
#include "components/MeshRenderer.hpp"  
#include "OpenGLModule.hpp"

namespace moul
{
    class UIPlayer : public sw::Component
    {
    public:
        sw::Vector2f m_pos;
        sw::Vector2f m_txtPos;
        std::string m_textureName;

        void update();
        void start();
        explicit UIPlayer(sw::GameObject& gameObject);
        ~UIPlayer() override;
    private:
        sw::Reference<sw::Sprite> m_sprite;
        sw::Reference<sw::Text> m_bomb;
        sw::Reference<sw::Text> m_speed;
        sw::Reference<sw::Text> m_range;
    }; // class UIPlayer
} // namespace moul


#endif // MOULERMAN_UIPLAYER_HPP