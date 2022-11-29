/*
** ShipWreck Engine , 2022
** Response.cpp
*/

#include <regex>
#include <iostream>

#include "boost/asio.hpp"

#include "experimental/Response.hpp"
#include "boost/static_string.hpp"

sw::network::Response::Response() :
m_httpVersion(),
m_statusMessage(),
m_header(),
m_body(),
m_statusCode(0)
{}

sw::network::Response::~Response()
= default;
//64852
void sw::network::Response::parseResponse(std::stringstream &stringstream)
{

    std::istream response_stream(stringstream.rdbuf());
    response_stream >> m_httpVersion;
    response_stream >> m_statusCode;
    std::getline(response_stream, m_statusMessage);
    m_statusMessage = m_statusMessage.substr(1, m_statusMessage.length() - 2);
    std::string header;
    std::stringstream ss;
    while (std::getline(response_stream, header) && header != "\r")
        ss << header;
    m_header = std::regex_replace( ss.str(), std::regex( "\\\r" ), "\n" );
}

const std::string &sw::network::Response::getHttpVersion() const
{
    return (m_httpVersion);
}

const std::string &sw::network::Response::getStatusMessage() const
{
    return (m_statusMessage);
}

const std::string &sw::network::Response::getHeader() const
{
    return (m_header);
}

const std::string &sw::network::Response::getBody() const
{
    return (m_body);
}

const unsigned int &sw::network::Response::getStatusCode() const
{
    return (m_statusCode);
}