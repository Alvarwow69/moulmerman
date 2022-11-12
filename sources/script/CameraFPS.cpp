/*
** ShipWreck Engine , 2022
** CameraFPS.cpp
*/

#include "window/Window.hpp"
#include "utils/Inputs.hpp"
#include "OpenGLModule.hpp"

#include "CameraFPS.hpp"

inc::CameraFPS::CameraFPS(sw::GameObject &gameObject) :
sw::Component(gameObject),
m_lastX(-1),
m_lastY(-1),
m_mouseSensitivity(0.1f)
{
    m_gameObject.scene().eventManager["Start"].subscribe(this, &inc::CameraFPS::start);
    m_gameObject.scene().eventManager["Update"].subscribe(this, &inc::CameraFPS::update);
}

void inc::CameraFPS::start()
{
    sw::ConcreteComponent auto& camera = m_gameObject.createComponent<sw::Camera>("CameraManager");

    camera.setClippingNear(0.1);
    camera.setProjection(sw::Camera::PERSPECTIVE);
    camera.setClippingFar(10000);
    camera.setPitch(-56);
    camera.setYaw(90);
    m_gameObject.transform().move(13.5, 27, -43);

}

void inc::CameraFPS::update()
{
    float speed = (sw::isKeyDown(sw::Keyboard::LSHIFT) ? 25.0f : 12.5f);
    float velocity = speed * sw::OpenGLModule::chrono().getElapsedTime();

    auto& cam = m_gameObject.getComponent<sw::Camera>("CameraManager");
    if (sw::isKeyDown(sw::Keyboard::W))                 //Z
        m_gameObject.transform().move(cam.getFront().x * velocity, cam.getFront().y * velocity, cam.getFront().z * velocity);
    if (sw::isKeyDown(sw::Keyboard::S))                 //S
        m_gameObject.transform().move(-cam.getFront().x * velocity, -cam.getFront().y * velocity, -cam.getFront().z * velocity);
    if (sw::isKeyDown(sw::Keyboard::Q))                 //A
        m_gameObject.transform().move(0, 0.1, 0);
    if (sw::isKeyDown(sw::Keyboard::D))                 //D
        m_gameObject.transform().move(cam.getRight().x * velocity, cam.getRight().y * velocity, cam.getRight().z * velocity);
    if (sw::isKeyDown(sw::Keyboard::A))                 //Q
        m_gameObject.transform().move(-cam.getRight().x * velocity, -cam.getRight().y * velocity, -cam.getRight().z * velocity);
    if (sw::isKeyDown(sw::Keyboard::E))                 //E
        m_gameObject.transform().move(0, -0.1, 0);
    if (sw::isKeyDown(sw::Keyboard::R))                 //R
        m_gameObject.transform().setPosition(0, 0, -3);

    if (sw::isMouseButtonDown(sw::MouseBtn::Button_right)) {
        sw::Window::SetEnableCursor(false);

        sw::Vector2f mousePos = sw::getMousePosition();
        if (m_lastY == -1) {
            m_lastX = mousePos.x;
            m_lastY = mousePos.y;
        }
        float xoffset = mousePos.x - m_lastX;
        float yoffset = m_lastY - mousePos.y;
        m_lastX = mousePos.x;
        m_lastY = mousePos.y;


        auto nPitch = cam.getPitch() + yoffset * m_mouseSensitivity;
        auto nYaw = cam.getYaw() + xoffset * m_mouseSensitivity;

        if (nPitch > 89.0f)
            nPitch = 89.0f;
        if (nPitch < -89.0f)
            nPitch = -89.0f;

        cam.setPitch(nPitch);
        cam.setYaw(nYaw);
    } else {
        sw::Window::SetEnableCursor(true);
        m_lastY = -1;
    }

    if (sw::isKeyPressed(sw::SPACE)) {
        std::cout << "Position: " << m_gameObject.transform().getGlobalPosition() << std::endl;
        std::cout << "Pitch: " << cam.getPitch() << std::endl;
        std::cout << "Yaw: " << cam.getYaw() << std::endl;
    }
}