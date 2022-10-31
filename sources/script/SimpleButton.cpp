/*
** ShipWreck Engine , 2022
** Button.cpp
*/

#include "script/SimpleButton.hpp"
#include "window/Window.hpp"
#include "utils/Inputs.hpp"
#include "OpenGLModule.hpp"

moul::SimpleButton::SimpleButton(sw::GameObject &gameObject) :
sw::Component(gameObject),
m_callback(nullptr)
{
    gameObject.scene().eventManager["Start"].subscribe(this, &moul::SimpleButton::start);
    gameObject.scene().eventManager["Update"].subscribe(this, &moul::SimpleButton::update);
}

void moul::SimpleButton::start()
{
    m_sprite.emplace(m_gameObject.createComponent<sw::Sprite>("SpriteManager").setTexture(m_textureName));
    m_gameObject.transform().setPosition(m_position);
    m_gameObject.transform().setScale(m_scale.x, m_scale.y, 0);
    m_text.emplace(m_gameObject.createComponent<sw::Text>("TextManager"));
    m_text.value().setText(m_buttonTitle).setPosition(m_position.x + m_txtPosition.x, sw::Window::GetSize().y - m_txtPosition.y - 40 - m_position.y);
}

void moul::SimpleButton::update()
{
    sw::Vector2f mousePos = sw::getMousePosition();
    sw::Vector3f pos = m_gameObject.transform().getGlobalPosition();
    auto width = m_sprite.value().getMaterial().texture->getWidth();
    auto height = m_sprite.value().getMaterial().texture->getHeight();

    if (mousePos.x >= pos.x && mousePos.x < pos.x + width * m_gameObject.transform().getScale().x
    && mousePos.y >= pos.y && mousePos.y < pos.y + height * m_gameObject.transform().getScale().y) {
        m_sprite.value().setColor(sw::Color{1.0f, 1.0f, 1.0f});
        if (sw::isMouseButtonPressed(sw::MouseBtn::Button_left))
            if (m_callback)
                m_callback(this);
    }
    else
        m_sprite.value().setColor(sw::Color{100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f});
}