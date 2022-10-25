/*
** Society: Creative Rift
** SHIPWRECK ENGINE, 2022
** Author: Guillaume S.
** File name: PlayerLoading.hpp
*/

#ifndef INCARIBUS_PLAYERLOADING_HPP
#define INCARIBUS_PLAYERLOADING_HPP

#include "components/base/Component.hpp"
#include "event/EventCollision.hpp"

namespace moul
{
    class IconLoading : public sw::Component
    {
    public:
        explicit IconLoading(sw::GameObject& gameObject);
        void start();
        void update();
    private:
        float m_animTime;

    }; // class Player
} // namespace moul

#endif //INCARIBUS_PLAYERLOADING_HPP
