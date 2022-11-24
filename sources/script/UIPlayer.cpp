/*
** ShipWreck Engine, 2022
** Player.cpp
*/

#include "UIPlayer.hpp"

moul::UIPlayer::UIPlayer(sw::GameObject& gameObject) :
sw::Component(gameObject)
{
    m_gameObject.scene().eventManager["Update"].subscribe(m_gameObject.name(), this, &moul::UIPlayer::update);
}

moul::UIPlayer::~UIPlayer() noexcept
{
}

void moul::UIPlayer::start()
{
    sw::Vector2f txtPos = {m_pos.x + m_txtPos.x, 1080 - 48 - m_pos.y - m_txtPos.y};

    m_sprite.emplace(m_gameObject.createComponent<sw::Sprite>("SpriteManager"));
    m_gameObject.transform().move(m_pos.x, m_pos.y, -2);
    m_sprite.value().setTexture(m_textureName);
    auto& txtBomb = m_gameObject.scene().createGameObject("Text_Bomb_" + m_gameObject.name());
    m_bomb.emplace(txtBomb.createComponent<sw::Text>("TextManager"));
    m_bomb.value().setText("PLACEHOLDER").setPosition(txtPos.x, txtPos.y - 83);
    auto& txtRange = m_gameObject.scene().createGameObject("Text_Range_" + m_gameObject.name());
    m_range.emplace(txtRange.createComponent<sw::Text>("TextManager"));
    m_range.value().setText("PLACEHOLDER").setPosition(txtPos.x, txtPos.y - 40);
    auto& txtSpeed = m_gameObject.scene().createGameObject("Text_Speed_" + m_gameObject.name());
    m_speed.emplace(txtSpeed.createComponent<sw::Text>("TextManager"));
    m_speed.value().setText("PLACEHOLDER").setPosition(txtPos.x, txtPos.y);

}

void moul::UIPlayer::update()
{
}