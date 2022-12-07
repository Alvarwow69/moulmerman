/*
** ShipWreck Engine , 2022
** BombModifier.hpp
*/

#ifndef MOULMERMAN_BOMBMODIFIER_HPP
#define MOULMERMAN_BOMBMODIFIER_HPP

#include "Modifier.hpp"

namespace moul
{
    class Player;

    class BombModifier : public Modifier
    {
    public:
        explicit BombModifier(sw::GameObject &gameObject);

        void applyModifier(Player& player) override;
        bool m_good;

    private:
    };
}

#endif //MOULMERMAN_BOMBMODIFIER_HPP
