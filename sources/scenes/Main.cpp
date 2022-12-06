/*
** Society: Creative Rift
** SHIPWRECK ENGINE, 2022
** Author: Guillaume S.
** File name: Main.cpp
** Description: [CHANGE]
*/

#include "scenes/Main.hpp"
#include "module/managers/SpriteManager.hpp"
#include "module/managers/CameraManager.hpp"
#include "module/managers/AudioSourceManager.hpp"
#include "OpenGLModule.hpp"
#include "scenes_manager/SceneLoadEvent.hpp"
#include "script/SimpleButton.hpp"
#include "window/Window.hpp"
#include "config/Config.hpp"

void Main::onLoad(sw::EventInfo& info)
{
    auto& scene = info.getInfo<sw::SceneLoadEvent>().scene;

    if (scene.name != "Main")
        return;
    auto& mainCamera = scene.createGameObject("MainCamera");
    auto& background = scene.createGameObject("Background");
    auto& play = scene.createGameObject("Button_Play");
    auto& setting = scene.createGameObject("Button_Setting");
    auto& credit = scene.createGameObject("Button_Credit");
    auto& exit = scene.createGameObject("Button_Exit");
    auto& title = scene.createGameObject("Title");
    auto& sceneLoader = scene.createGameObject("SceneLoader");

    auto& loader = sceneLoader.createComponent<inc::SceneLoader>("ScriptManager");
    loader.m_switchAuto = true;
    sw::ConcreteComponent auto& camera = mainCamera.createComponent<sw::Camera>("CameraManager");
    sw::ConcreteComponent auto& camAudio = mainCamera.createComponent<sw::AudioSource>("AudioManager");
    camAudio.addAudio("Menu_music").setPlayOnStart(true).setVolume(.5f).play();
    camera.setClippingNear(-1);
    std::string back("MainMenuBack");
    background.createComponent<sw::Sprite>("SpriteManager").setTexture(back);
    background.setLayer("SpriteManager", 1);

    auto& cpt_play = play.createComponent<moul::SimpleButton>("ScriptManager");
    cpt_play.m_textureName = "Button_Play";
    cpt_play.m_position = {200, 400, 0};
    cpt_play.m_callback = [](moul::SimpleButton *button) {
        sw::Config::GetConfig()["Data"]["NewScene"] = "SelectionScene";
        sw::OpenGLModule::sceneManager().loadScene("LoadingScene");
    };

    auto& cpt_settings = setting.createComponent<moul::SimpleButton>("ScriptManager");
    cpt_settings.m_textureName = "Button_Setting";
    cpt_settings.m_position = {650, 500, 0};
    cpt_settings.m_callback = [](moul::SimpleButton *button) {
        sw::OpenGLModule::sceneManager().loadScene("Settings");
    };
    auto& cpt_credit = credit.createComponent<moul::SimpleButton>("ScriptManager");
    cpt_credit.m_textureName = "Button_Credit";
    cpt_credit.m_position = {650, 350, 0};
    cpt_credit.m_callback = [](moul::SimpleButton *button) {
        sw::OpenGLModule::sceneManager().loadScene("Credits");
    };
    auto& cpt_exit = exit.createComponent<moul::SimpleButton>("ScriptManager");
    cpt_exit.m_textureName = "Button_Exit";
    cpt_exit.m_position = {650, 700, 0};
    cpt_exit.m_callback = [](moul::SimpleButton *button) {
        sw::Window::CloseWindow();
    };

    auto& text = title.createComponent<sw::Text>("TextManager");
    text.setText("Moulmerman");
    text.setFont("PixelFont");
    text.setPosition(475, 900);
    text.setColor(sw::WhiteColor);
    text.setSize(2);
}