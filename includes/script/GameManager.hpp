/*
** ShipWreck Engine , 2022
** GameManager.hpp
*/

#ifndef MOULMERMAN_GAMEMANAGER_HPP
#define MOULMERMAN_GAMEMANAGER_HPP

#include "components/Components.hpp"
#include "generator/MapGenerator.hpp"

namespace moul
{
    class GameManager : public sw::Component
    {
    public:
        explicit GameManager(sw::GameObject& gameObject);

        void start();
        void update();
    private:
        sw::Reference<MapGenerator> m_mapGenerator;
    };
}

#endif //MOULMERMAN_GAMEMANAGER_HPP
