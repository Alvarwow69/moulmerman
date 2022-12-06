/*
** ShipWreck Engine , 2022
** MapGenerator.hpp
*/

#ifndef MOULMERMAN_MAPGENERATOR_HPP
#define MOULMERMAN_MAPGENERATOR_HPP

#include <vector>
#include "utils/Vector2.hpp"
#include "components/Components.hpp"

namespace moul
{
    class MapGenerator : public sw::Component
    {
    public:
        explicit MapGenerator(sw::GameObject& gameObject);

        void start();
        void generateMap(int with, int height);
        void generateProcedural();
        void generateBasicMap();
        void generateVisual();
        void generatePlayers(int playerNbr);

        [[nodiscard]] std::vector<std::string>& getMap();

        sw::Vector3f m_origin;
        sw::Vector2i m_size;
    private:
        std::vector<std::string> m_map;
        bool m_basic;

        void processBasicPlayers(int playerNbr);
        void processNonBasicPlayers(int playerNbr);
    }; //class MapGenerator
} // namespace moul

#endif //MOULMERMAN_MAPGENERATOR_HPP
