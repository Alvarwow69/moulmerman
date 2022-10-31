/*
** ShipWreck Engine , 2022
** SettingsScene.cpp
*/

#include "scenes/SettingsScene.hpp"
#include "scenes_manager/SceneLoadEvent.hpp"
#include "components/Components.hpp"
#include "script/SimpleButton.hpp"
#include "window/Window.hpp"
#include "OpenGLModule.hpp"

void moul::SettingsScene::onLoad(sw::EventInfo &info)
{
    auto& scene = info.getInfo<sw::SceneLoadEvent>().scene;

    if (scene.name != "Settings")
        return;

    auto& mainCamera = scene.createGameObject("MainCamera");
    sw::ConcreteComponent auto& camera = mainCamera.createComponent<sw::Camera>("CameraManager");
    camera.setClippingNear(-1);

    auto& background = scene.createGameObject("Background");
    std::string back("Background_Selection");
    background.createComponent<sw::Sprite>("SpriteManager").setTexture(back);
    background.setLayer("SpriteManager", 1);

    auto& title = scene.createGameObject("Title");
    title.createComponent<sw::Text>("TextManager").setText("Settings").setPosition(170, 900).setColor(sw::Color(1, 1, 1));

    auto& fullscreen = scene.createGameObject("FullScreen_Btn");
    auto& config = fullscreen.createComponent<moul::SimpleButton>("ScriptManager");
    config.m_textureName = "Button_large";
    config.m_txtPosition = {40, 40, 0};
    config.m_position = {200, 400, 0};
    config.m_buttonTitle = "Toggle fullscreen";
    config.m_scale = {3, 3};
    config.m_callback = [](SimpleButton *button) { sw::Window::ToggleFullScreen(); };

    auto& exit = scene.createGameObject("Exit_btn");
    auto& exitbtn = exit.createComponent<moul::SimpleButton>("ScriptManager");
    exitbtn.m_textureName = "Button_large";
    exitbtn.m_txtPosition = {40, 20, 0};
    exitbtn.m_position = {1500, 900, 0};
    exitbtn.m_buttonTitle = "Main menu";
    exitbtn.m_scale = {2, 2};
    exitbtn.m_callback = [](SimpleButton *button) { sw::OpenGLModule::sceneManager().loadScene("Main"); };
}