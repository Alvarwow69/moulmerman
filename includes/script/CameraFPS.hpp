/*
** ShipWreck Engine , 2022
** CameraFPS.hpp
*/

#ifndef INCARIBUS_CAMERAFPS_HPP
#define INCARIBUS_CAMERAFPS_HPP

#include "components/Components.hpp"

namespace inc
{
    class CameraFPS : public sw::Component {
    public:
        explicit CameraFPS(sw::GameObject& gameObject);
        void start();
        void update();
    private:
        float m_lastX;
        float m_lastY;
        float m_offX;
        float m_offY;
        float m_mouseSensitivity;

    }; // class CameraFPS
} // namespace inc

#endif //INCARIBUS_CAMERAFPS_HPP
