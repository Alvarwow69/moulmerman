/*
** ShipWreck Engine , 2022
** EndGameResume.cpp
*/

#include "EndGameResume.hpp"
#include "boost/json/serialize.hpp"
#include "config/Config.hpp"

const std::string names[4] = {"Player1", "Player2", "Player3", "Player4"};

moul::EndGameResume::EndGameResume(sw::GameObject &gameObject) :
sw::Component(gameObject),
m_request{"HOST", "http", "/api/games"}
{
    gameObject.scene().eventManager["Start"].subscribe(m_gameObject.name(), this, &moul::EndGameResume::start);

}

void moul::EndGameResume::start()
{
    auto conf = sw::Config::GetConfig()["Setting"];
    auto& info = m_body["infos"].emplace_object();
    for (int i = 0; i < 4; i++) {
        auto player = conf[names[i]];
        if (player["type"].as<std::string>() == "No Player")
            continue;
        auto newPlayer = boost::json::object();
        newPlayer.emplace("name", player["name"].as<std::string>());
        newPlayer.emplace("rank", player["rank"].as<std::string>());

        info[names[i]] = newPlayer;
    }
    info["GameStart"] = conf["GameStart"].as<std::string>();
    std::cout << boost::json::serialize(m_body) << std::endl;
    //m_request.sendRequest(m_body);
}

void moul::EndGameResume::update()
{

}