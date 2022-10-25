/*
** ShipWreck Engine , 2022
** SettingsScene.hpp
*/

#ifndef MOULMERMAN_SETTINGSSCENE_HPP
#define MOULMERMAN_SETTINGSSCENE_HPP

#include <string>
#include "event/EventInfo.hpp"

namespace moul
{
    class SettingsScene
    {
    public:
        std::string name() {return ("ye");}
        void onLoad(sw::EventInfo& info);
    }; // class SettingsScene
} // namespace moul

#endif //MOULMERMAN_SETTINGSSCENE_HPP
