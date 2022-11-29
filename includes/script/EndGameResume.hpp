/*
** ShipWreck Engine , 2022
** EndGameResume.hpp
*/

#ifndef MOULMERMAN_ENDGAMERESUME_HPP
#define MOULMERMAN_ENDGAMERESUME_HPP

#include "components/Components.hpp"
#include "experimental/Request.hpp"

namespace moul
{
    class EndGameResume : public sw::Component
    {
    public:
        explicit EndGameResume(sw::GameObject& gameObject);

        void start();
        void update();

        boost::json::object m_body;

    private:
        sw::network::Request m_request;
    };
}

#endif //MOULMERMAN_ENDGAMERESUME_HPP
