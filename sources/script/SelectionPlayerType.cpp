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
    m_gameObject.scene().eventManager["Start"].subscribe(this, &moul::SelectionPlayerType::start);
    m_gameObject.scene().eventManager["Update"].subscribe(this, &moul::SelectionPlayerType::update);
}

std::string GetStringType(moul::SelectionPlayerType::Type type)
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

moul::SelectionPlayerType::Type NextType(moul::SelectionPlayerType::Type type)
{
    switch (type) {
        case moul::SelectionPlayerType::Type::PLAYER:
            return moul::SelectionPlayerType::Type::AI;
        case moul::SelectionPlayerType::Type::AI:
            return moul::SelectionPlayerType::Type::NONE;
        default:
            return moul::SelectionPlayerType::Type::PLAYER;
    }
}

void moul::SelectionPlayerType::start()
{
    m_text.emplace(m_gameObject.createComponent<sw::Text>("TextManager"));
    m_text.value().setText(GetStringType(m_type)).setPosition(m_textPos.x, m_textPos.y);
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