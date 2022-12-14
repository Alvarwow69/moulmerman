/*
** Society: Creative Rift
** SHIPWRECK ENGINE, 2022
** Author: Guillaume S.
** File name: Main.hpp
** Description: [CHANGE]
*/

#ifndef MOULMERMAN_MAIN_HPP
#define MOULMERMAN_MAIN_HPP

#include "event/EventInfo.hpp"
#include "utils/tree/aabb.hpp"

class Main{
    public:
        std::string name() {return ("ye");}
        void onLoad(sw::EventInfo& info);
        sw::tree::tree<int, float> m_tree;
};

#endif //MOULMERMAN_MAIN_HPP
