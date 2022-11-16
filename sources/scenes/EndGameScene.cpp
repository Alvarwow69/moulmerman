/*
** ShipWreck Engine , 2022
** CreditScene.cpp
*/

#include "OpenGLModule.hpp"
#include "scenes/EndGameScene.hpp"
#include "scenes_manager/SceneLoadEvent.hpp"
#include "components/Components.hpp"
#include "script/CameraFPS.hpp"
#include "script/EndPlayer.hpp"
#include "script/SimpleButton.hpp"

void moul::EndGameScene::onLoad(sw::EventInfo &info)
{
    auto& scene = info.getInfo<sw::SceneLoadEvent>().scene;

    if (scene.name != "EndGame")
        return;

    auto& mainCamera = scene.createGameObject("MainCamera");
    sw::ConcreteComponent auto& camera = mainCamera.createComponent<inc::CameraFPS>("ScriptManager");

    auto& map = scene.createGameObject("Map");
    map.transform().scale(3.5f, 3.5f, 3.5f);
    auto& mapMesh = map.createComponent<sw::MeshRenderer>("MeshRendererManager", "EngGameMap");

    auto& directLight = scene.createGameObject("DirLight");
    auto& directLightCpt = directLight.createComponent<sw::Light>("LightManager");
    mapMesh.attachLight("DirLight");
    directLightCpt.m_ambient = {1.0f, 1.0f, 1.0f};

    auto& player1 = scene.createGameObject("Player1");
    auto& model1 = player1.createComponent<moul::EndPlayer>("ScriptManager");
    model1.m_modelName = "Player1";
    model1.m_animName = "Player_dancing";
    model1.m_textPos = {1400, 340};
    player1.transform().scale(30, 30, 30);
    player1.transform().setPosition(17, 0, -16);
    player1.transform().rotate(90);

    auto& player2 = scene.createGameObject("Player2");
    auto& model2 = player2.createComponent<moul::EndPlayer>("ScriptManager");
    model2.m_modelName = "Player2";
    model2.m_animName = "Player_head";
    model2.m_textPos = {1075, 340};
    player2.transform().scale(30, 30, 30);
    player2.transform().setPosition(17, 0, -26);
    player2.transform().rotate(90);

    auto& player3 = scene.createGameObject("Player3");
    auto& model3 = player3.createComponent<moul::EndPlayer>("ScriptManager");
    model3.m_modelName = "Player3";
    model3.m_animName = "Player_idle";
    model3.m_textPos = {700, 340};
    player3.transform().scale(30, 30, 30);
    player3.transform().setPosition(18, 0, -36);
    player3.transform().rotate(90);

    auto& player4 = scene.createGameObject("Player4");
    auto& model4 = player4.createComponent<moul::EndPlayer>("ScriptManager");
    model4.m_modelName = "Player4";
    model4.m_animName = "Player_dying";
    model4.m_textPos = {400, 340};
    player4.transform().scale(30, 30, 30);
    player4.transform().setPosition(18, 0, -48);
    player4.transform().rotate(90);

    auto& exit = scene.createGameObject("Exit_btn");
    auto& exitbtn = exit.createComponent<moul::SimpleButton>("ScriptManager");
    exitbtn.m_textureName = "Button_large";
    exitbtn.m_txtPosition = {40, 20, -1};
    exitbtn.m_position = {100, 900, 0};
    exitbtn.m_buttonTitle = "Main Menu";
    exitbtn.m_scale = {2, 2};
    exitbtn.m_callback = [](SimpleButton *button) {
        sw::OpenGLModule::sceneManager().loadScene("Main");
    };
}