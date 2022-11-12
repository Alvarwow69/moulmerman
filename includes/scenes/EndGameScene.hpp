/*
** ShipWreck Engine , 2022
** EndGame.hpp
*/

#ifndef MOULMERMAN_ENDGAME_HPP
#define MOULMERMAN_ENDGAME_HPP

#include <string>
#include "event/EventInfo.hpp"

namespace moul
{
    class EndGameScene
    {
    public:
        std::string name() {return ("ye");}
        void onLoad(sw::EventInfo& info);
    }; // class EndGameScene
} // namespace moul

#endif //MOULMERMAN_ENDGAME_HPP
