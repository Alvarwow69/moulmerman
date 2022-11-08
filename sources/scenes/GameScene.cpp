/*
** ShipWreck Engine , 2022
** GameScene.cpp
*/

#include "scenes/GameScene.hpp"
#include "scenes_manager/SceneLoadEvent.hpp"
#include "components/Components.hpp"
#include "script/CameraFPS.hpp"
#include "script/GameManager.hpp"

void moul::GameScene::onLoad(sw::EventInfo &info)
{
    auto& scene = info.getInfo<sw::SceneLoadEvent>().scene;

    if (scene.name != "Game")
        return;

    auto& mainCamera = scene.createGameObject("MainCamera");
    sw::ConcreteComponent auto& camera = mainCamera.createComponent<inc::CameraFPS>("ScriptManager");

    auto& gameManager = scene.createGameObject("GameManager");
    gameManager.createComponent<moul::GameManager>("ScriptManager");
}