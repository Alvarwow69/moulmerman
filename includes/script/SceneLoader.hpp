/*
** ShipWreck Engine , 2022
** SceneLoader.hpp
*/

#ifndef INCARIBUS_SCENELOADER_HPP
#define INCARIBUS_SCENELOADER_HPP

#include "components/Components.hpp"
#include "utils/async/AsyncScene.hpp"

namespace inc
{
    class SceneLoader : public sw::Component
    {
    private:
        std::shared_ptr<sw::AsyncScene> m_operation;
        sw::Reference<sw::GameObject> m_text;
        bool m_isRunning;
        std::string m_nextScene;

    public:
        std::string m_sceneToLoad;
        bool m_switchAuto;
        std::string m_displayedText;
        std::string m_font;
        sw::Vector2f m_textPos;

        explicit SceneLoader(sw::GameObject& gameObject);
        ~SceneLoader() override;
        void start();
        void update();
        void startLoad();
    };
} // namespace inc

#endif //INCARIBUS_SCENELOADER_HPP
