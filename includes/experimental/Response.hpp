/*
** ShipWreck Engine , 2022
** Response.hpp
*/

#ifndef SHIPWRECK_ENGINE_INSTALLER_RESPONSE_HPP
#define SHIPWRECK_ENGINE_INSTALLER_RESPONSE_HPP

#include <string>
#include <sstream>

namespace sw::network
{
    class Response
    {
    public:
        explicit Response();
        ~Response();

        void parseResponse(std::stringstream &stringstream);
        [[nodiscard]] const std::string& getHttpVersion() const;
        [[nodiscard]] const std::string& getStatusMessage() const;
        [[nodiscard]] const std::string& getHeader() const;
        [[nodiscard]] const std::string& getBody() const;
        [[nodiscard]] const unsigned int& getStatusCode() const;
    private:
        std::string m_httpVersion;
        std::string m_statusMessage;
        std::string m_header;
        std::string m_body;
        unsigned int m_statusCode;

    };
}

#endif //SHIPWRECK_ENGINE_INSTALLER_RESPONSE_HPP
