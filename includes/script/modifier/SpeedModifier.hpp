/*
** ShipWreck Engine , 2022
** BombModifier.hpp
*/

#ifndef MOULMERMAN_SPEEDMODIFIER_HPP
#define MOULMERMAN_SPEEDMODIFIER_HPP

#include "Modifier.hpp"

namespace moul
{
    class Player;

    class SpeedModifier : public Modifier
    {
    public:
        explicit SpeedModifier(sw::GameObject &gameObject);

        void applyModifier(Player& player) override;

    private:
        bool m_good;
    };
}

#endif //MOULMERMAN_SPEEDMODIFIER_HPP
