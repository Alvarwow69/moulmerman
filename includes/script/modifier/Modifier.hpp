/*
** ShipWreck Engine , 2022
** Modifier.hpp
*/

#ifndef MOULMERMAN_MODIFIER_HPP
#define MOULMERMAN_MODIFIER_HPP

#include "components/Components.hpp"

namespace moul
{
    class Player;

    class Modifier : public sw::Component
    {
    public:
        std::string m_modelName;

        explicit Modifier(sw::GameObject &gameObject);
        virtual ~Modifier();

        void start();
        void update();

        virtual void applyModifier(Player& player) = 0;
    protected:
        sw::Reference<sw::MeshRenderer> m_meshRenderer;
        sw::Reference<sw::AudioSource> m_audioSource;
        float m_animTime;
    };
}

#endif //MOULMERMAN_MODIFIER_HPP
