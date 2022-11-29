/*
** ShipWreck Engine , 2022
** Request.hpp
*/

#ifndef SHIPWRECK_ENGINE_INSTALLER_REQUEST_HPP
#define SHIPWRECK_ENGINE_INSTALLER_REQUEST_HPP

#include <string>

#include "boost/asio.hpp"
#include "boost/beast.hpp"
#include "boost/json/object.hpp"
#include "Response.hpp"

namespace sw::network {

    class Request {
    public:
        Response response;

        Request() = delete;
        Request(std::string host, std::string port, std::string path = "/", int version = 11);
        ~Request();

        void sendRequest();
        void sendRequest(boost::json::object& body);
    private:
        static boost::asio::io_context m_ioc;
        std::string m_host;
        std::string m_port;
        std::string m_path;
        std::stringstream m_response;
        int m_version;
        boost::beast::http::request<boost::beast::http::string_body> m_request;
        boost::beast::tcp_stream m_stream;

        void connect();
        void setUpRequest();
        void setUpRequest(boost::json::object& body);
    };

} // namespace sw::network

#endif //SHIPWRECK_ENGINE_INSTALLER_REQUEST_HPP
