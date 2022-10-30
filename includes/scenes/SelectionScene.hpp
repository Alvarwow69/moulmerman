/*
** ShipWreck Engine , 2022
** LoadingScene.hpp
*/

#ifndef MOULMERMAN_SELECTIONSCENE_HPP
#define MOULMERMAN_SELECTIONSCENE_HPP

#include <string>
#include "event/EventInfo.hpp"

namespace moul
{
    class SelectionScene
    {
    public:
        std::string name() {return ("ye");}
        void onLoad(sw::EventInfo& info);
    }; // class Loading Scene
} // namespace moul

#endif //MOULMERMAN_SELECTIONSCENE_HPP
