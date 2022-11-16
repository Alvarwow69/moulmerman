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

    scene.eventManager.create("PlayerDie");

    auto& mainCamera = scene.createGameObject("MainCamera");
    sw::ConcreteComponent auto& camera = mainCamera.createComponent<sw::Camera>("CameraManager");
    mainCamera.transform().move(13.5, 27, -43);
    camera.setClippingNear(0.1);
    camera.setClippingFar(10000);
    camera.setPitch(-56);
    camera.setYaw(90);

    auto& gameManager = scene.createGameObject("GameManager");
    gameManager.createComponent<moul::GameManager>("ScriptManager");

    auto& map = scene.createGameObject("Map");
    map.transform().scale(3.5f, 3.5f, 3.5f);
    auto& mapMesh = map.createComponent<sw::MeshRenderer>("MeshRendererManager", "Game_map");

    auto& directLight = scene.createGameObject("DirLight");
    auto& directLightCpt = directLight.createComponent<sw::Light>("LightManager");
    mapMesh.attachLight("DirLight");
    directLightCpt.m_ambient = {0.6f, 0.6f, 0.6f};
    directLightCpt.m_diffuse = {0.6f, 0.6f, 0.6f};

    //auto& pointLight = scene.createGameObject("PointLight");
    //auto& pointLightCpt = pointLight.createComponent<sw::Light>("LightManager");
    //mapMesh.attachLight("PointLight");
    //pointLightCpt.setLightType(sw::Light::POINT);
    //pointLight.transform().setPosition({4.5f, 3.6f, -30});
}