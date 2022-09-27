/*
** Society: Creative Rift
** SHIPWRECK ENGINE, 2022
** Author: Guillaume S.
** File name: Project.cpp
** Description: [CHANGE]
*/

#include "OpenGLModule.hpp"
#include "Project.hpp"
#include "Main.hpp"

void sw::CreateScenes()
{
    auto main = new Main();
    sw::OpenGLModule::eventManager().create("SceneLoad");
    sw::OpenGLModule::sceneManager().createScene("Main");
    sw::OpenGLModule::sceneManager().createScene("MainFile");
    sw::OpenGLModule::sceneManager().createScene("Game");

    sw::OpenGLModule::eventManager()["SceneLoad"].subscribe(main, &Main::onLoad);
}