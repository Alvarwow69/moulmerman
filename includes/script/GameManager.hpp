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
        enum GameState {
            NONE,
            PREGAME,
            COUNTDOWN,
            INGAME,
            PAUSE,
            POSTGAME
        };
        explicit GameManager(sw::GameObject& gameObject);

        void start();
        void update();

        [[nodiscard]] static GameState GetGameState();
    private:
        void countdown();
        void displayPauseMenu();
        void playerDie();

        sw::Reference<MapGenerator> m_mapGenerator;
        sw::Reference<sw::AudioSource> m_audio;
        sw::Reference<sw::Text> m_text;
        static GameState m_gameState;
        double m_countdown;
        int m_nextStep;
        int m_playerLeft;
    };
}

#endif //MOULMERMAN_GAMEMANAGER_HPP
