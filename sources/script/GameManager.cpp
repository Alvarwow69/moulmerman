/*
** ShipWreck Engine , 2022
** GameManager.cpp
*/

#include "OpenGLModule.hpp"
#include "window/Window.hpp"

#include "script/GameManager.hpp"
#include "config/Config.hpp"
#include "Player.hpp"
#include "script/UIPlayer.hpp"

const sw::Vector3f positions[4] = {{7.5f, 3.6f, -35.5f}, {19.5f, 3.6f, -23.5f}, {7.5f, 3.6f, -23.5f}, {19.5f, 3.6f, -35.5f}};
const std::string names[4] = {"Player1", "Player2", "Player3", "Player4"};

moul::GameManager::GameState moul::GameManager::m_gameState = NONE;
sw::Reference<moul::MapGenerator> moul::GameManager::m_mapGenerator;

moul::GameManager::GameManager(sw::GameObject &gameObject) :
sw::Component(gameObject),
m_countdown(0.0),
m_playerLeft(0)
{
    gameObject.scene().eventManager["Start"].subscribe(m_gameObject.name(), this, &moul::GameManager::start);
    gameObject.scene().eventManager["Update"].subscribe(m_gameObject.name(), this, &moul::GameManager::update);
    gameObject.scene().eventManager["PlayerDie"].subscribe(m_gameObject.name(), this, &moul::GameManager::playerDie);
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

    m_gameObject.scene().eventManager.create("Collision");
    spawnPlayers();
}

void moul::GameManager::update()
{
    if (m_gameState == PREGAME)
        m_gameState = COUNTDOWN;
    if (m_gameState == COUNTDOWN)
        countdown();
    if (m_gameState == POSTGAME)
        postGame();
    if (m_gameState == PAUSE)
        displayPauseMenu();
    if (sw::isKeyPressed(sw::P))
        m_gameState = (m_gameState == PAUSE ? INGAME : PAUSE);
    if (sw::isKeyDown(sw::E) && sw::isKeyDown(sw::R))
        m_gameState = POSTGAME;
}

void moul::GameManager::countdown()
{
    auto oui = sw::OpenGLModule::deltaTime();
    m_countdown += oui;
    if (m_countdown > 4 && m_nextStep == 5) {
        m_audio.value().play("StartGo");
        m_text.value().setActive(false);
        m_gameState = INGAME;
        m_countdown = 0;
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

moul::MapGenerator& moul::GameManager::GetMap()
{
    return (m_mapGenerator.value());
}

void moul::GameManager::playerDie()
{
    m_playerLeft--;
    if (m_playerLeft == 0)
        m_gameState = POSTGAME;
}

void CreateUI(sw::Scene& scene, int i, std::string name)
{
    auto& UIP1 = scene.getGameObject("UI" + name).createComponent<moul::UIPlayer>("ScriptManager");

    switch (i) {
        case 0:
            UIP1.m_pos = {0, 0};
            UIP1.m_txtPos = {320, 90};
            UIP1.m_textureName = "UIPlayer1";
            break;
        case 1:
            UIP1.m_pos = {1480, 845};
            UIP1.m_textureName = "UIPlayer2";
            UIP1.m_txtPos = {65, 65};
            break;
        case 2:
            UIP1.m_pos = {1480, 0};
            UIP1.m_textureName = "UIPlayer3";
            UIP1.m_txtPos = {65, 80};
            break;
        default:
            UIP1.m_pos = {0, 845};
            UIP1.m_textureName = "UIPlayer4";
            UIP1.m_txtPos = {320, 70};
            break;
    }
    UIP1.start();
}

void moul::GameManager::spawnPlayers()
{
    auto conf = sw::Config::GetConfig()["Setting"];

    for (int i = 0; i < conf.size(); i++) {
        auto player = conf[names[i]];
        if (player["type"].as<std::string>() == "No Player")
            continue;
        auto& newPlayer = m_gameObject.scene().createGameObject(player["name"].as<std::string>());
        auto& newPlayerCpt = newPlayer.createComponent<moul::Player>("ScriptManager");
        CreateUI(m_gameObject.scene(), i, names[i]);
        newPlayerCpt.m_modelName = names[i];
        newPlayer.transform().setPosition(positions[m_playerLeft]);
        newPlayer.transform().scale(8, 8, 8);
        newPlayer.transform().rotate(180);
        newPlayerCpt.m_bombtxt.emplace(m_gameObject.scene().getGameObject("Text_Bomb_UI" + names[i]).getComponent<sw::Text>("TextManager"));
        newPlayerCpt.m_speedtxt.emplace(m_gameObject.scene().getGameObject("Text_Speed_UI" + names[i]).getComponent<sw::Text>("TextManager"));
        newPlayerCpt.m_rangetxt.emplace(m_gameObject.scene().getGameObject("Text_Range_UI" + names[i]).getComponent<sw::Text>("TextManager"));

        /*
        sw::Vector2f min = ...
        sw::Vector2f max = ...
        */
        auto &trans = newPlayer.transform().getPosition();
        //auto &size = newPlayer.getComponent<sw::BoxCollider>("BoxColliderManager").getSize();

        sw::Vector2f min{trans.z - 0.25f, trans.x - 0.25f};
        sw::Vector2f max{min.x + 0.5f, min.y + 0.5f};
        newPlayer.id = i + 800;
        m_gameObject.scene().m_tree.insert(newPlayer.id, min, max);
        m_gameObject.scene().m_lut.emplace(newPlayer.id, newPlayerCpt);
        newPlayerCpt.start();
        m_playerLeft++;
    }
}

void moul::GameManager::postGame()
{
    m_countdown += sw::OpenGLModule::deltaTime();

    if (m_countdown >= 5)
        sw::OpenGLModule::sceneManager().loadScene("EndGame");
}