/*
** ShipWreck Engine , 2022
** CreditScene.hpp
*/

#ifndef MOULMERMAN_CREDITSCENE_HPP
#define MOULMERMAN_CREDITSCENE_HPP

#include <string>
#include "event/EventInfo.hpp"

namespace moul
{
    class CreditScene
    {
    public:
        std::string name() {return ("ye");}
        void onLoad(sw::EventInfo& info);
    }; // class CreditScene
} // namespace moul

#endif //MOULMERMAN_CREDITSCENE_HPP
