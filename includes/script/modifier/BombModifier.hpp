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

    private:
        bool m_good;
    };
}

#endif //MOULMERMAN_BOMBMODIFIER_HPP
