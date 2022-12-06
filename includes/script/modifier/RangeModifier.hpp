/*
** ShipWreck Engine , 2022
** BombModifier.hpp
*/

#ifndef MOULMERMAN_RANGEMODIFIER_HPP
#define MOULMERMAN_RANGEMODIFIER_HPP

#include "Modifier.hpp"

namespace moul
{
    class Player;

    class RangeModifier : public Modifier
    {
    public:
        explicit RangeModifier(sw::GameObject &gameObject);

        void applyModifier(Player& player) override;

    private:
        bool m_good;
    };
}

#endif //MOULMERMAN_RANGEMODIFIER_HPP
