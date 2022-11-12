/*
** ShipWreck Engine , 2022
** GameManager.cpp
*/

#include "OpenGLModule.hpp"
#include "window/Window.hpp"

#include "script/GameManager.hpp"

moul::GameManager::GameState moul::GameManager::m_gameState = NONE;

moul::GameManager::GameManager(sw::GameObject &gameObject) :
sw::Component(gameObject),
m_mapGenerator(),
m_countdown(0.0)
{
    gameObject.scene().eventManager["Start"].subscribe(this, &moul::GameManager::start);
    gameObject.scene().eventManager["Update"].subscribe(this, &moul::GameManager::update);
    gameObject.scene().eventManager["PlayerDie"].subscribe(this, &moul::GameManager::playerDie);
}

void moul::GameManager::start()
{
    m_gameState = PREGAME;
    auto& mapGen = m_gameObject.scene().createGameObject("MapGenerator");
    m_mapGenerator.emplace(mapGen.createComponent<moul::MapGenerator>("ScriptManager"));
    m_mapGenerator.value().m_origin = {6.0f, 3.6f, -36};
    m_mapGenerator.value().generateMap(13, 13);
    m_mapGenerator.value().generateBasicMap();
    m_mapGenerator.value().generatePlayers(4);
    m_mapGenerator.value().generateVisual();

    m_audio.emplace(m_gameObject.createComponent<sw::AudioSource>("AudioManager"));
    m_nextStep = 1;

    m_text.emplace(m_gameObject.createComponent<sw::Text>("TextManager"));
    m_text.value().setText("4");
    m_text.value().setPosition(900, 500);
}

void moul::GameManager::update()
{
    if (m_gameState == PREGAME)
        m_gameState = COUNTDOWN;
    if (m_gameState == COUNTDOWN)
        countdown();
    if (m_gameState == POSTGAME)
        sw::OpenGLModule::sceneManager().loadScene("EndGame");
    if (m_gameState == PAUSE)
        displayPauseMenu();
    if (sw::isKeyPressed(sw::P))
        m_gameState = (m_gameState == PAUSE ? INGAME : PAUSE);
}

void moul::GameManager::countdown()
{
    m_countdown += sw::OpenGLModule::chrono().getElapsedTime();
    if (m_countdown > 4 && m_nextStep == 5) {
        m_audio.value().play("StartGo");
        m_text.value().setActive(false);
        m_gameState = INGAME;
    } else if (m_countdown > 3 && m_nextStep == 4) {
        m_audio.value().play("Start1");
        m_text.value().setText("1");
        m_nextStep = 5;
    } else if (m_countdown > 2 && m_nextStep == 3) {
        m_audio.value().play("Start2");
        m_text.value().setText("2");
        m_nextStep = 4;
    } else if (m_countdown > 1 && m_nextStep == 2) {
        m_audio.value().stop();
        m_audio.value().play("Start3");
        m_text.value().setText("3");
        m_nextStep = 3;
    } else if (m_countdown > 0 && m_nextStep == 1) {
        m_audio.value().play("Start4");
        m_nextStep = 2;
    }
}

void moul::GameManager::displayPauseMenu()
{

}

moul::GameManager::GameState moul::GameManager::GetGameState()
{
    return (m_gameState);
}

void moul::GameManager::playerDie()
{
    m_playerLeft--;
    if (m_playerLeft == 0)
        m_gameState = POSTGAME;
}