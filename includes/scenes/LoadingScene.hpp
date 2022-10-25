/*
** ShipWreck Engine , 2022
** LoadingScene.hpp
*/

#ifndef MOULMERMAN_LOADINGSCENE_HPP
#define MOULMERMAN_LOADINGSCENE_HPP

#include <string>
#include "event/EventInfo.hpp"

namespace moul
{
    class LoadingScene
    {
    public:
        std::string name() {return ("ye");}
        void onLoad(sw::EventInfo& info);
    }; // class Loading Scene
} // namespace moul

#endif //MOULMERMAN_LOADINGSCENE_HPP
