/*
** ShipWreck Engine , 2022
** LoadingScene.cpp
*/

#include "scenes/SelectionScene.hpp"
#include "scenes_manager/SceneLoadEvent.hpp"
#include "components/MeshRenderer.hpp"
#include "script/SelectionPlayer.hpp"
#include "script/SimpleButton.hpp"
#include "OpenGLModule.hpp"

void moul::SelectionScene::onLoad(sw::EventInfo &info)
{
    auto& scene = info.getInfo<sw::SceneLoadEvent>().scene;

    if (scene.name != "SelectionScene")
        return;

    auto& mainCamera = scene.createGameObject("MainCamera");
    sw::ConcreteComponent auto& camera = mainCamera.createComponent<sw::Camera>("CameraManager");
    camera.setClippingNear(0.1);
    camera.setProjection(sw::Camera::PERSPECTIVE);
    camera.setClippingFar(1000);
    mainCamera.transform().move(0, 0, 15);

    auto& building = scene.createGameObject("Building");
    auto& model = building.createComponent<sw::MeshRenderer>("MeshRendererManager", "Selection_scene");
    building.transform().setPosition(0, -8, 13);
    building.transform().setRotation(180, 0, 1, 0);

    auto& directLight = scene.createGameObject("DirLight");
    auto& directLightCpt = directLight.createComponent<sw::Light>("LightManager");
    model.attachLight("DirLight");
    directLightCpt.m_ambient = {1.0f, 1.0f, 1.0f};

    auto& player1 = scene.createGameObject("Player1");
    auto& model1 = player1.createComponent<moul::SelectionPlayer>("ScriptManager");
    model1.m_modelName = "Player1";
    model1.m_textPos = {1400, 340};
    player1.transform().scale(8, 8, 8);
    player1.transform().setPosition(3.5, -1.1, 8);
    player1.transform().rotate(-20);

    auto& player2 = scene.createGameObject("Player2");
    auto& model2 = player2.createComponent<moul::SelectionPlayer>("ScriptManager");
    model2.m_modelName = "Player2";
    model2.m_textPos = {1075, 340};
    player2.transform().scale(8, 8, 8);
    player2.transform().setPosition(1.3, -1.1, 8);
    player2.transform().rotate(-10);

    auto& player3 = scene.createGameObject("Player3");
    auto& model3 = player3.createComponent<moul::SelectionPlayer>("ScriptManager");
    model3.m_modelName = "Player3";
    model3.m_textPos = {700, 340};
    player3.transform().scale(8, 8, 8);
    player3.transform().setPosition(-1.3, -1.1, 8);
    player3.transform().rotate(10);

    auto& player4 = scene.createGameObject("Player4");
    auto& model4 = player4.createComponent<moul::SelectionPlayer>("ScriptManager");
    model4.m_modelName = "Player4";
    model4.m_textPos = {400, 340};
    player4.transform().scale(8, 8, 8);
    player4.transform().setPosition(-3.5, -1.1, 8);
    player4.transform().rotate(20);

    auto& play = scene.createGameObject("Play_btn");
    auto& playbtn = play.createComponent<moul::SimpleButton>("ScriptManager");
    playbtn.m_textureName = "Button_large";
    playbtn.m_txtPosition = {40, 20, 0};
    playbtn.m_position = {1500, 900, 0};
    playbtn.m_buttonTitle = "Play";
    playbtn.m_scale = {2, 2};
    playbtn.m_callback = [](SimpleButton *button) {
        button->gameObject().scene().getGameObject("Player1").getComponent<moul::SelectionPlayer>("ScriptManager").saveConf();
        button->gameObject().scene().getGameObject("Player2").getComponent<moul::SelectionPlayer>("ScriptManager").saveConf();
        button->gameObject().scene().getGameObject("Player3").getComponent<moul::SelectionPlayer>("ScriptManager").saveConf();
        button->gameObject().scene().getGameObject("Player4").getComponent<moul::SelectionPlayer>("ScriptManager").saveConf();
        sw::OpenGLModule::sceneManager().loadScene("Game");
    };

    auto& exit = scene.createGameObject("Exit_btn");
    auto& exitbtn = exit.createComponent<moul::SimpleButton>("ScriptManager");
    exitbtn.m_textureName = "Button_large";
    exitbtn.m_txtPosition = {40, 20, 0};
    exitbtn.m_position = {100, 900, 0};
    exitbtn.m_buttonTitle = "Main Menu";
    exitbtn.m_scale = {2, 2};
    exitbtn.m_callback = [](SimpleButton *button) {
        sw::OpenGLModule::sceneManager().loadScene("Main");
    };
}