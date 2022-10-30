/*
** ShipWreck Engine , 2022
** SelectionPlayer.hpp
*/

#ifndef MOULMERMAN_SELECTIONPLAYERTYPE_HPP
#define MOULMERMAN_SELECTIONPLAYERTYPE_HPP

#include "components/Components.hpp"

namespace moul
{
    class SelectionPlayerType : public sw::Component
    {
    public:
        enum Type {
            PLAYER,
            AI,
            NONE
        };
        sw::Vector2f m_textPos;

        explicit SelectionPlayerType(sw::GameObject& gameobject, Type type = Type::NONE);

        void start();
        void update();
        moul::SelectionPlayerType::Type getType();
    private:
        Type m_type;
        sw::Reference<sw::Text> m_text;
    };
}

#endif //MOULMERMAN_SELECTIONPLAYERTYPE_HPP
