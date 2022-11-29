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
#include "script/EndGameResume.hpp"
#include "config/Config.hpp"

void moul::EndGameScene::onLoad(sw::EventInfo &info)
{
    auto& scene = info.getInfo<sw::SceneLoadEvent>().scene;

    if (scene.name != "EndGame")
        return;
    auto conf = sw::Config::GetConfig()["Setting"];
    std::string ranking[4] = {"NONE", "NONE", "NONE", "NONE"};

    ranking[conf["Player1"]["rank"].as<int>() - 1] = "Player1";
    ranking[conf["Player2"]["rank"].as<int>() - 1] = "Player2";
    ranking[conf["Player3"]["rank"].as<int>() - 1] = "Player3";
    ranking[conf["Player4"]["rank"].as<int>() - 1] = "Player4";

    auto& mainCamera = scene.createGameObject("MainCamera");
    //sw::ConcreteComponent auto& camera = mainCamera.createComponent<inc::CameraFPS>("ScriptManager");
    sw::ConcreteComponent auto& camera = mainCamera.createComponent<sw::Camera>("CameraManager");
    mainCamera.transform().move(45.5, 4, -29);
    camera.setClippingNear(0.01);
    camera.setClippingFar(10000);
    camera.setPitch(0.8);
    camera.setYaw(180);

    auto& map = scene.createGameObject("Map");
    map.transform().scale(3.5f, 3.5f, 3.5f);
    auto& mapMesh = map.createComponent<sw::MeshRenderer>("MeshRendererManager", "EngGameMap");

    auto& directLight = scene.createGameObject("DirLight");
    auto& directLightCpt = directLight.createComponent<sw::Light>("LightManager");
    mapMesh.attachLight("DirLight");
    directLightCpt.m_ambient = {1.0f, 1.0f, 1.0f};

    if (conf["Player1"]["type"].as<std::string>() != "No Player") {
        auto& player1 = scene.createGameObject("Player1");
        auto& model1 = player1.createComponent<moul::EndPlayer>("ScriptManager");
        model1.m_modelName = ranking[0];
        model1.m_animName = "Player_dancing";
        model1.m_textPos = {1400, 340};
        player1.transform().scale(30, 30, 30);
        player1.transform().setPosition(17, 0, -16);
        player1.transform().rotate(90);
    }

    if (conf["Player2"]["type"].as<std::string>() != "No Player") {
        auto &player2 = scene.createGameObject("Player2");
        auto &model2 = player2.createComponent<moul::EndPlayer>("ScriptManager");
        model2.m_modelName = ranking[1];
        model2.m_animName = "Player_head";
        model2.m_textPos = {1075, 340};
        player2.transform().scale(30, 30, 30);
        player2.transform().setPosition(17, 0, -26);
        player2.transform().rotate(90);
    }

    if (conf["Player3"]["type"].as<std::string>() != "No Player") {
        auto &player3 = scene.createGameObject("Player3");
        auto &model3 = player3.createComponent<moul::EndPlayer>("ScriptManager");
        model3.m_modelName = ranking[2];
        model3.m_animName = "Player_idle";
        model3.m_textPos = {700, 340};
        player3.transform().scale(30, 30, 30);
        player3.transform().setPosition(18, 0, -36);
        player3.transform().rotate(90);
    }

    if (conf["Player4"]["type"].as<std::string>() != "No Player") {
        auto &player4 = scene.createGameObject("Player4");
        auto &model4 = player4.createComponent<moul::EndPlayer>("ScriptManager");
        model4.m_modelName = ranking[3];
        model4.m_animName = "Player_dying";
        model4.m_textPos = {400, 340};
        player4.transform().scale(30, 30, 30);
        player4.transform().setPosition(18, 0, -48);
        player4.transform().rotate(90);
    }

    auto& exit = scene.createGameObject("Exit_btn");
    auto& exitbtn = exit.createComponent<moul::SimpleButton>("ScriptManager");
    exitbtn.m_textureName = "Button_large";
    exitbtn.m_txtPosition = {40, 20, -1};
    exitbtn.m_position = {100, 900, -2};
    exitbtn.m_buttonTitle = "Main Menu";
    exitbtn.m_scale = {2, 2};
    exitbtn.m_callback = [](SimpleButton *button) {
        sw::OpenGLModule::sceneManager().loadScene("Main");
    };
    mainCamera.addChild("Exit_btn");

    auto& resume = scene.createGameObject("Resume");
    resume.createComponent<moul::EndGameResume>("ScriptManager");
}