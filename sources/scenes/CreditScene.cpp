/*
** ShipWreck Engine , 2022
** CreditScene.cpp
*/

#include "scenes/CreditScene.hpp"
#include "scenes_manager/SceneLoadEvent.hpp"
#include "components/Components.hpp"
#include "script/BackToScene.hpp"

void moul::CreditScene::onLoad(sw::EventInfo &info)
{
    auto& scene = info.getInfo<sw::SceneLoadEvent>().scene;

    if (scene.name != "Credits")
        return;

    auto& mainCamera = scene.createGameObject("MainCamera");
    sw::ConcreteComponent auto& camera = mainCamera.createComponent<sw::Camera>("CameraManager");
    camera.setClippingNear(-1);

    auto& background = scene.createGameObject("Background");
    std::string back("Background_Credit");
    background.createComponent<sw::Sprite>("SpriteManager").setTexture(back).setColor(sw::Color(100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f));
    background.setLayer("SpriteManager", 1);

    auto& title = scene.createGameObject("Title");
    title.createComponent<sw::Text>("TextManager").setText("Credits:").setPosition(170, 900).setColor(sw::YellowColor);

    auto& dev = scene.createGameObject("Developer");
    dev.createComponent<sw::Text>("TextManager").setText("Developer / Game Designer:").setPosition(170, 600).setColor(sw::YellowColor);

    auto& gs = scene.createGameObject("Text_Gs");
    gs.createComponent<sw::Text>("TextManager").setText(" - Guillaume Soisson").setPosition(170, 600 - 60).setColor(sw::YellowColor);
    auto& gd = scene.createGameObject("Text_Gd");
    gd.createComponent<sw::Text>("TextManager").setText(" - Guillaume Debard").setPosition(170, 600 - 60 * 2).setColor(sw::YellowColor);
    auto& fg = scene.createGameObject("Text_Fg");
    fg.createComponent<sw::Text>("TextManager").setText(" - Florian Golling").setPosition(170, 600 - 60 * 3).setColor(sw::YellowColor);

    auto& sound = scene.createGameObject("SoundDesigner");
    sound.createComponent<sw::Text>("TextManager").setText("Sound Designer:").setPosition(800, 600).setColor(sw::YellowColor);
    auto& qf = scene.createGameObject("Text_Qf");
    qf.createComponent<sw::Text>("TextManager").setText(" - Quentin Feuillard").setPosition(800, 600 - 60).setColor(sw::YellowColor);

    auto& return_txt = scene.createGameObject("ReturnTxt");
    return_txt.createComponent<sw::Text>("TextManager").setText("Press SPACE to return to the Main menu").setPosition(500, 100).setColor(sw::MagentaColor);

    auto& backToScene = scene.createGameObject("BackToScene");
    backToScene.createComponent<moul::BackToScene>("ScriptManager", "Main");
}