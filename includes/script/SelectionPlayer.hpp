/*
** ShipWreck Engine , 2022
** SelectionPlayer.hpp
*/

#ifndef MOULMERMAN_SELECTIONPLAYER_HPP
#define MOULMERMAN_SELECTIONPLAYER_HPP

#include "components/Components.hpp"
#include "SelectionPlayerType.hpp"
#include "SelectionPlayerName.hpp"
#include "components/MeshRenderer.hpp"

namespace moul
{
    class SelectionPlayer : public sw::Component
    {
    public:
        std::string m_modelName;
        sw::Vector2f m_textPos;

        explicit SelectionPlayer(sw::GameObject& gameobject);

        void start();
        void update();
        void saveConf();
    private:
        sw::Reference<SelectionPlayerType> m_type;
        sw::Reference<SelectionPlayerName> m_name;
        sw::Reference<sw::MeshRenderer> m_mesh;
    };
}

#endif //MOULMERMAN_SELECTIONPLAYER_HPP
