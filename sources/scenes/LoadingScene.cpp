/*
** ShipWreck Engine , 2022
** LoadingScene.cpp
*/

#include "scenes/LoadingScene.hpp"
#include "scenes_manager/SceneLoadEvent.hpp"
#include "components/Components.hpp"
#include "script/IconLoading.hpp"
#include "script/SceneLoader.hpp"
#include "config/Config.hpp"

void moul::LoadingScene::onLoad(sw::EventInfo &info)
{
    auto& scene = info.getInfo<sw::SceneLoadEvent>().scene;

    if (scene.name != "LoadingScene")
        return;

    auto& mainCamera = scene.createGameObject("MainCamera");
    sw::ConcreteComponent auto& camera = mainCamera.createComponent<sw::Camera>("CameraManager");
    camera.setClippingNear(-1);

    auto& background = scene.createGameObject("Background");
    std::string back("Loading_Screen");
    background.createComponent<sw::Sprite>("SpriteManager").setTexture(back);
    background.setLayer("SpriteManager", 1);

    auto& icon = scene.createGameObject("Icon");
    icon.createComponent<moul::IconLoading>("ScriptManager");

    auto& loader = scene.createGameObject("SceneLoader");
    auto& cpt_loader = loader.createComponent<inc::SceneLoader>("ScriptManager");
    cpt_loader.m_sceneToLoad = sw::Config::GetConfig()["Data"]["NewScene"].as<std::string>();
    cpt_loader.m_displayedText = "Press SPACE to continue...";
    cpt_loader.m_textPos = {380, 900};
    cpt_loader.startLoad();
}