/*
** ShipWreck Engine , 2022
** CreditScene.cpp
*/

#include "scenes/EndGameScene.hpp"
#include "scenes_manager/SceneLoadEvent.hpp"
#include "components/Components.hpp"

void moul::EndGameScene::onLoad(sw::EventInfo &info)
{
    auto& scene = info.getInfo<sw::SceneLoadEvent>().scene;

    if (scene.name != "EndGame")
        return;

    auto& mainCamera = scene.createGameObject("MainCamera");
    sw::ConcreteComponent auto& camera = mainCamera.createComponent<sw::Camera>("CameraManager");
    camera.setClippingNear(-1);
}