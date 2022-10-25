/*
** ShipWreck Engine , 2022
** SceneLoader.cpp
*/

#include "script/SceneLoader.hpp"
#include "OpenGLModule.hpp"
#include "window/Window.hpp"
#include "config/Config.hpp"

inc::SceneLoader::SceneLoader(sw::GameObject &gameObject) :
sw::Component(gameObject),
m_isRunning(false),
m_switchAuto(false)
{
    gameObject.scene().eventManager["Start"].subscribe(this, &inc::SceneLoader::start);
    gameObject.scene().eventManager["Update"].subscribe(this, &inc::SceneLoader::update);
}

inc::SceneLoader::~SceneLoader() noexcept
= default;

void inc::SceneLoader::start()
{
    if (!m_switchAuto) {
        m_text = m_gameObject.scene().createGameObject("LoadingText");
        auto& textCpt = m_text.value().createComponent<sw::Text>("TextManager");
        textCpt.setPosition(m_textPos.x, m_textPos.y)
            .setText(m_displayedText)
            .setColor(sw::Color(105.0f / 255.0f, 166.0f / 255.0f, 31.0f / 255.0f))
            .setFont(m_font);
        m_text.value().setActive(false);
    }
}

void inc::SceneLoader::update()
{
    if (!m_isRunning)
        return;
    if (m_operation->isDone()) {
        if (!m_switchAuto)
            m_text.value().setActive(true);
        if (m_switchAuto || sw::isKeyDown(sw::Keyboard::SPACE))
            sw::OpenGLModule::sceneManager().swapSceneFromAsync(*m_operation, m_nextScene);
    }
}

void inc::SceneLoader::startLoad()
{
    m_isRunning = true;
    if (m_gameObject.scene().name != "LoadingScene") {
        sw::Config::GetConfig()["Data"]["NewScene"] = m_sceneToLoad;
        m_operation = sw::OpenGLModule::sceneManager().loadSceneAsync("LoadingScene");
        m_nextScene = "LoadingScene";
    } else {
        m_operation = sw::OpenGLModule::sceneManager().loadSceneAsync(m_sceneToLoad);
        m_nextScene = m_sceneToLoad;
    }
}