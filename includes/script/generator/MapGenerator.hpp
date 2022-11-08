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

        void generateMap(int with, int height);
        void generateProcedural();
        void generateBasicMap();
        void generateVisual();
        void generatePlayers(int playerNbr);

        [[nodiscard]] const std::vector<std::string>& getMap() const;

        sw::Vector3f m_origin;
    private:
        sw::Vector2i m_size;
        std::vector<std::string> m_map;
        bool m_basic;

        void processBasicPlayers(int playerNbr);
        void processNonBasicPlayers(int playerNbr);
    }; //class MapGenerator
} // namespace moul

#endif //MOULMERMAN_MAPGENERATOR_HPP
