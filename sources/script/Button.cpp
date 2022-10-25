/*
** ShipWreck Engine , 2022
** Button.cpp
*/

#include "script/Button.hpp"
#include "window/Window.hpp"
#include "utils/Inputs.hpp"

moul::Button::Button(sw::GameObject &gameObject) :
sw::Component(gameObject)
{
    gameObject.scene().eventManager["Start"].subscribe(this, &moul::Button::start);
    gameObject.scene().eventManager["Update"].subscribe(this, &moul::Button::update);
}

void moul::Button::start()
{
    m_sprite.emplace(m_gameObject.createComponent<sw::Sprite>("SpriteManager").setTexture(m_textureName));
    m_gameObject.transform().setPosition(m_position);
    m_sprite.value().setColor(sw::Color{100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f});
    m_loader.emplace(m_gameObject.scene().getGameObject("SceneLoader").getComponent<inc::SceneLoader>("ScriptManager"));
}

void moul::Button::update()
{
    sw::Vector2f mousePos = sw::getMousePosition();
    sw::Vector3f pos = m_gameObject.transform().getPosition();
    auto width = m_sprite.value().getMaterial().texture->getWidth();
    auto height = m_sprite.value().getMaterial().texture->getHeight();

    if (mousePos.x >= pos.x && mousePos.x < pos.x + width * m_gameObject.transform().getScale().x
    && mousePos.y >= pos.y && mousePos.y < pos.y + height * m_gameObject.transform().getScale().y) {
        m_sprite.value().setColor(sw::Color{1.0f, 1.0f, 1.0f});
        if (sw::isMouseButtonPressed(sw::MouseBtn::Button_left)) {
            m_loader.value().m_sceneToLoad = m_scene;
            m_loader.value().startLoad();
        }
    }
    else
        m_sprite.value().setColor(sw::Color{100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f});
}