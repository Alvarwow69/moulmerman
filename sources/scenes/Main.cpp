/*
** Society: Creative Rift
** SHIPWRECK ENGINE, 2022
** Author: Guillaume S.
** File name: Main.cpp
** Description: [CHANGE]
*/

#include "scenes/Main.hpp"
#include "module/gameObject/GameObject.hpp"
#include "module/managers/SpriteManager.hpp"
#include "module/managers/CameraManager.hpp"
#include "module/managers/TextManager.hpp"
#include "module/managers/AudioSourceManager.hpp"
#include "OpenGLModule.hpp"
#include "scenes_manager/SceneLoadEvent.hpp"

void Main::onLoad(sw::EventInfo& info)
{
    auto& scene = info.getInfo<sw::SceneLoadEvent>().scene;

    if (scene.name != "Main")
        return;
    scene.eventManager.create("Collision");

    auto& mainCamera = scene.createGameObject("MainCamera");
    sw::ConcreteComponent auto& camera = mainCamera.createComponent<sw::Camera>("CameraManager");
    sw::ConcreteComponent auto& camAudio = mainCamera.createComponent<sw::AudioSource>("AudioManager");
    camera.setClippingNear(-1);
}