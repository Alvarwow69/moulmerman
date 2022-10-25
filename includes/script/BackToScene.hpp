/*
** ShipWreck Engine , 2022
** BackToScene.hpp
*/

#ifndef MOULMERMAN_BACKTOSCENE_HPP
#define MOULMERMAN_BACKTOSCENE_HPP

#include "components/Components.hpp"

namespace moul
{
    class BackToScene : public sw::Component
    {
    public:
        std::string m_sceneToBack;

        explicit BackToScene(sw::GameObject& gameObject, std::string sceneToBack);
        void update();
    };
} // namespace moul

#endif //MOULMERMAN_BACKTOSCENE_HPP
