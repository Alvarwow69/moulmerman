/*
** ShipWreck Engine , 2022
** SelectionPlayerName.cpp
*/

#include "SelectionPlayerName.hpp"
#include "window/Window.hpp"
#include "utils/Inputs.hpp"

moul::SelectionPlayerName::SelectionPlayerName(sw::GameObject &gameobject) :
sw::Component(gameobject),
m_selected(false)
{
    m_gameObject.scene().eventManager["Start"].subscribe(m_gameObject.name(), this, &moul::SelectionPlayerName::start);
    m_gameObject.scene().eventManager["Update"].subscribe(m_gameObject.name(), this, &moul::SelectionPlayerName::update);
}

void moul::SelectionPlayerName::start()
{
    m_text.emplace(m_gameObject.createComponent<sw::Text>("TextManager"));
    m_text.value().setText(m_playerName).setPosition(m_textPos.x, m_textPos.y).setFont("PixelFont");
}

void moul::SelectionPlayerName::update()
{
    sw::Vector2f mousePos = sw::getMousePosition();
    bool hover = false;

    m_text.value().setColor(sw::Color(0, 0, 0));
    if (mousePos.x >= m_textPos.x && mousePos.x < m_textPos.x + 200
        && sw::Window::GetSize().y - mousePos.y >= m_textPos.y && sw::Window::GetSize().y - mousePos.y < m_textPos.y + 50) {
        m_text.value().setColor(sw::Color(1, 0, 0));
        hover = true;
    }

    if (m_selected)
        m_text.value().setColor(sw::Color(1, 0, 0));

    if (sw::isMouseButtonReleased(sw::MouseBtn::Button_left)) {
        if (hover)
            m_selected = true;
        else {
            m_text.value().setColor(sw::Color(0, 0, 0));
            m_selected = false;
        }
    }

    sw::Keyboard key = sw::GetKeyPressed();
    int shift = (sw::isKeyDown(sw::LSHIFT) || sw::isKeyDown(sw::RSHIFT) ? 0 : 32);
    if (m_selected) {
        if (key != sw::UNKNOWN && m_playerName.length() < 10)
            m_playerName.push_back((char)(key + shift));

        if (sw::isKeyPressed(sw::BACKSPACE) && m_playerName.length() > 0)
            m_playerName.pop_back();
        m_text.value().setText(m_playerName);

    }
}
