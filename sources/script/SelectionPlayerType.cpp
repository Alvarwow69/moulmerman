/*
** ShipWreck Engine , 2022
** SelectionPlayerType.cpp
*/

#include "SelectionPlayerType.hpp"
#include "window/Window.hpp"
#include "utils/Inputs.hpp"

moul::SelectionPlayerType::SelectionPlayerType(sw::GameObject &gameobject, moul::SelectionPlayerType::Type type) :
sw::Component(gameobject),
m_type(type)
{
    m_gameObject.scene().eventManager["Update"].subscribe(m_gameObject.name(), this, &moul::SelectionPlayerType::update);
}

std::string moul::SelectionPlayerType::GetStringType(moul::SelectionPlayerType::Type type)
{
    switch (type) {
        case moul::SelectionPlayerType::Type::PLAYER:
            return "Player";
        case moul::SelectionPlayerType::Type::AI:
            return "AI";
        default:
            return "No Player";
    }
}

moul::SelectionPlayerType::Type moul::SelectionPlayerType::NextType(moul::SelectionPlayerType::Type type)
{
    if (!m_must)
        switch (type) {
            case moul::SelectionPlayerType::Type::PLAYER:
                return moul::SelectionPlayerType::Type::AI;
            case moul::SelectionPlayerType::Type::AI:
                return moul::SelectionPlayerType::Type::NONE;
            default:
                return moul::SelectionPlayerType::Type::PLAYER;
        }
    else
        return (type == moul::SelectionPlayerType::PLAYER ? moul::SelectionPlayerType::Type::AI : moul::SelectionPlayerType::Type::PLAYER);
}

void moul::SelectionPlayerType::start()
{
    if (m_must)
        m_type = PLAYER;
    m_text.emplace(m_gameObject.createComponent<sw::Text>("TextManager"));
    m_text.value().setText(GetStringType(m_type)).setPosition(m_textPos.x, m_textPos.y).setFont("PixelFont");
}

void moul::SelectionPlayerType::update()
{
    sw::Vector2f mousePos = sw::getMousePosition();

    m_text.value().setColor(sw::BlackColor);
    if (mousePos.x >= m_textPos.x && mousePos.x < m_textPos.x + 200
        && sw::Window::GetSize().y - mousePos.y >= m_textPos.y && sw::Window::GetSize().y - mousePos.y < m_textPos.y + 50) {
        m_text.value().setColor(sw::RedColor);
        if (sw::isMouseButtonReleased(sw::MouseBtn::Button_left)) {
            m_type = NextType(m_type);
            m_text.value().setText(GetStringType(m_type));
        }
    }
}

moul::SelectionPlayerType::Type moul::SelectionPlayerType::getType()
{
    return (m_type);
}

std::string moul::SelectionPlayerType::getTypeName()
{
    return (GetStringType(m_type));
}