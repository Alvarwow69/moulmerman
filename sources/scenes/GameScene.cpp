/*
** ShipWreck Engine , 2022
** GameScene.cpp
*/

#include "OpenGLModule.hpp"
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

    sw::OpenGLModule::eventManager().create("PlayerDie");

    auto& mainCamera = scene.createGameObject("MainCamera");
    sw::ConcreteComponent auto& camera = mainCamera.createComponent<inc::CameraFPS>("ScriptManager");

    auto& gameManager = scene.createGameObject("GameManager");
    gameManager.createComponent<moul::GameManager>("ScriptManager");

    auto& map = scene.createGameObject("Map");
    map.transform().scale(3.5f, 3.5f, 3.5f);
    auto& mapMesh = map.createComponent<sw::MeshRenderer>("MeshRendererManager", "Game_map");

    auto& directLight = scene.createGameObject("DirLight");
    auto& directLightCpt = directLight.createComponent<sw::Light>("LightManager");
    mapMesh.attachLight("DirLight");
    directLightCpt.m_ambient = {0.6f, 0.6f, 0.6f};

    //auto& pointLight = scene.createGameObject("PointLight");
    //auto& pointLightCpt = pointLight.createComponent<sw::Light>("LightManager");
    //mapMesh.attachLight("PointLight");
    //pointLightCpt.setLightType(sw::Light::POINT);
    //pointLight.transform().setPosition({4.5f, 3.6f, -30});
}