/*
** ShipWreck Engine , 2022
** BackToScene.cpp
*/

#include "BackToScene.hpp"
#include "window/Window.hpp"
#include "utils/Inputs.hpp"
#include "OpenGLModule.hpp"

moul::BackToScene::BackToScene(sw::GameObject &gameObject, std::string sceneToBack) :
sw::Component(gameObject),
m_sceneToBack(sceneToBack)
{
    gameObject.scene().eventManager["Update"].subscribe(this, &moul::BackToScene::update);
}

void moul::BackToScene::update()
{
    if (sw::isKeyPressed(sw::Keyboard::SPACE))
        sw::OpenGLModule::sceneManager().loadScene(m_sceneToBack);
}