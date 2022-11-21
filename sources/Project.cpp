/*
** Society: Creative Rift
** SHIPWRECK ENGINE, 2022
** Author: Guillaume S.
** File name: Project.cpp
** Description: [CHANGE]
*/

#include "OpenGLModule.hpp"
#include "Project.hpp"
#include "Main.hpp"
#include "LoadingScene.hpp"
#include "CreditScene.hpp"
#include "SettingsScene.hpp"
#include "SelectionScene.hpp"
#include "GameScene.hpp"
#include "EndGameScene.hpp"

void sw::CreateScenes()
{
    auto main = new Main();
    auto loading = new moul::LoadingScene();
    auto credit = new moul::CreditScene();
    auto settings = new moul::SettingsScene();
    auto selection = new moul::SelectionScene();
    auto game = new moul::GameScene();
    auto endGame = new moul::EndGameScene();
    sw::OpenGLModule::eventManager().create("SceneLoad");
    sw::OpenGLModule::sceneManager().createScene("Main");
    sw::OpenGLModule::sceneManager().createScene("LoadingScene");
    sw::OpenGLModule::sceneManager().createScene("SelectionScene");
    sw::OpenGLModule::sceneManager().createScene("Credits");
    sw::OpenGLModule::sceneManager().createScene("Settings");
    sw::OpenGLModule::sceneManager().createScene("Game");
    sw::OpenGLModule::sceneManager().createScene("EndGame");

    sw::OpenGLModule::eventManager()["SceneLoad"].subscribe("Main", main, &Main::onLoad);
    sw::OpenGLModule::eventManager()["SceneLoad"].subscribe("Loading", loading, &moul::LoadingScene::onLoad);
    sw::OpenGLModule::eventManager()["SceneLoad"].subscribe("Credit", credit, &moul::CreditScene::onLoad);
    sw::OpenGLModule::eventManager()["SceneLoad"].subscribe("Settings", settings, &moul::SettingsScene::onLoad);
    sw::OpenGLModule::eventManager()["SceneLoad"].subscribe("Selection", selection, &moul::SelectionScene::onLoad);
    sw::OpenGLModule::eventManager()["SceneLoad"].subscribe("Game", game, &moul::GameScene::onLoad);
    sw::OpenGLModule::eventManager()["SceneLoad"].subscribe("EndGame", endGame, &moul::EndGameScene::onLoad);
}