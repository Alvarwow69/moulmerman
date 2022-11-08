/*
** ShipWreck Engine , 2022
** GameScene.hpp
*/

#ifndef MOULMERMAN_GAMESCENE_HPP
#define MOULMERMAN_GAMESCENE_HPP

#include <string>
#include "event/EventInfo.hpp"

namespace moul
{
    class GameScene
    {
    public:
        std::string name() {return ("ye");}
        void onLoad(sw::EventInfo& info);
    }; // class GameScene
} // namespace moul

#endif //MOULMERMAN_GAMESCENE_HPP
