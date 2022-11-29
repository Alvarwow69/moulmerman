/*
** ShipWreck Engine , 2022
** Request.cpp
*/

#include "experimental/Request.hpp"
#include "boost/json/serialize.hpp"
#include <utility>
#include <iostream>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

boost::asio::io_context sw::network::Request::m_ioc{};

sw::network::Request::Request(std::string host, std::string port, std::string path, int version) :
m_host(std::move(host)),
m_port(std::move(port)),
m_path(std::move(path)),
m_response(),
m_version(version),
m_request(),
m_stream(m_ioc)
{}

sw::network::Request::~Request()
= default;

void sw::network::Request::connect()
{
    boost::asio::ip::tcp::resolver resolver(m_ioc);
    auto const results = resolver.resolve(m_host, m_port);

    m_stream.connect(results);
}

void sw::network::Request::setUpRequest()
{
    http::request<http::string_body> req{http::verb::get, m_path, m_version};
    req.set(http::field::host, m_host);
    req.set(http::field::user_agent, "Moulerman");
    req.set(http::field::accept, "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");

    m_request = req;
}

void sw::network::Request::setUpRequest(boost::json::object& body)
{
    http::request<http::string_body> req{http::verb::get, m_path, m_version};
    req.set(http::field::host, m_host);
    req.set(http::field::user_agent, "Moulerman");
    req.set(http::field::accept, "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");
    req.set(http::field::body, boost::json::serialize(body));

    m_request = req;
}

void sw::network::Request::sendRequest()
{
    try {
        connect();
        setUpRequest();
        http::write(m_stream, m_request);

        beast::flat_buffer buffer;
        http::response<http::file_body> res;
        beast::error_code ecc;
        res.body().open("beast.rar", beast::file_mode::write_new, ecc);
        http::read(m_stream, buffer, res);

        //m_response << res;
        //response.parseResponse(m_response);
        beast::error_code ec;
        m_stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        if(ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};

    } catch (const std::exception &e)  {
        std::cerr << e.what() << std::endl;
    }
}

void sw::network::Request::sendRequest(boost::json::object& body)
{
    try {
        connect();
        setUpRequest();
        http::write(m_stream, m_request);

        beast::flat_buffer buffer;
        http::response<http::file_body> res;
        beast::error_code ecc;
        res.body().open("beast.rar", beast::file_mode::write_new, ecc);
        http::read(m_stream, buffer, res);

        //m_response << res;
        //response.parseResponse(m_response);
        beast::error_code ec;
        m_stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        if(ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};

    } catch (const std::exception &e)  {
        std::cerr << e.what() << std::endl;
    }
}