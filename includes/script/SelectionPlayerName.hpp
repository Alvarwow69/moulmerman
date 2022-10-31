/*
** ShipWreck Engine , 2022
** SelectionPlayer.hpp
*/

#ifndef MOULMERMAN_SELECTIONPLAYERNAME_HPP
#define MOULMERMAN_SELECTIONPLAYERNAME_HPP

#include "components/Components.hpp"

namespace moul
{
    class SelectionPlayerName : public sw::Component
    {
    public:
        sw::Vector2f m_textPos;
        std::string m_playerName;

        explicit SelectionPlayerName(sw::GameObject& gameobject);

        void start();
        void update();
    private:
        sw::Reference<sw::Text> m_text;
        bool m_selected;
    };
}

#endif //MOULMERMAN_SELECTIONPLAYERNAME_HPP
