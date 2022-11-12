/*
** ShipWreck Engine , 2022
** SelectionPlayer.hpp
*/

#ifndef MOULMERMAN_ENDPLAYER_HPP
#define MOULMERMAN_ENDPLAYER_HPP

#include "components/Components.hpp"
#include "SelectionPlayerType.hpp"
#include "SelectionPlayerName.hpp"
#include "components/MeshRenderer.hpp"

namespace moul
{
    class EndPlayer : public sw::Component
    {
    public:
        std::string m_modelName;
        std::string m_animName;
        sw::Vector2f m_textPos;

        explicit EndPlayer(sw::GameObject& gameObject);

        void start();
        void update();
    private:
        sw::Reference<sw::MeshRenderer> m_mesh;
    };
}

#endif //MOULMERMAN_ENDPLAYER_HPP
