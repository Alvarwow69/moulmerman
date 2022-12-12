/*
** ShipWreck Engine , 2022
** BombModifier.hpp
*/

#ifndef MOULMERMAN_NINJAMODIFIER_HPP
#define MOULMERMAN_NINJAMODIFIER_HPP

#include "Modifier.hpp"

namespace moul
{
    class Player;

    class NinjaModifier : public Modifier
    {
    public:
        explicit NinjaModifier(sw::GameObject &gameObject);

        void applyModifier(AI& player);
        void applyModifier(Player& player) override;
        bool m_good;

    private:
    };
}

#endif //MOULMERMAN_NINJAMODIFIER_HPP
