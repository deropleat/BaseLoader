#include "CBase.h"

CBase::CBase()
{
}

CBase::CBase(std::string url)
{
    this->url = url;
    if (url.find('\\') != std::string::npos || url.find("/") == std::string::npos)
    {
        std::string string;
        std::ifstream base(url, std::ios::in | std::ios::binary);
        if (base.is_open())
        {
            while (std::getline(base, string)) this->response += string + '\n';
            this->response = this->response.substr(0, this->response.length() - 1);
            base.close();
        }
        this->contentLength = this->response.length();
    }
    else
    {
        this->response = requests::SendHTTP_GET(this->url);
        this->contentLength = atoi(this->getHeader("Content-Length").c_str());
    }
}

void CBase::resolveContentLength(size_t destSize)
{
    size_t diffSize = destSize - this->getContentLength() - 1;
    this->response += '\n' + std::string(diffSize, '0');
}

std::string CBase::getHeader()
{
    if (this->url.find('\\') != std::string::npos || url.find("/") == std::string::npos) return "";
    if (this->response.empty()) return this->response;

    size_t endPos = this->response.find("\r\n\r\n");
    if (endPos != std::string::npos) return this->response.substr(0, endPos);

    return this->response;
}

std::string CBase::getHeader(std::string param)
{
    if (this->url.find('\\') != std::string::npos || url.find("/") == std::string::npos) return "";
    std::string header = this->getHeader();
    if (header.empty()) return header;

    header = header.substr(header.find(param + ": ") + param.length() + 2);
    return header.substr(0, header.find("\r\n"));
}

std::string CBase::getResponse()
{
    if (this->url.find('\\') != std::string::npos || url.find("/") == std::string::npos || this->response.empty()) return this->response;

    size_t startPos = this->response.find("\r\n\r\n");
    if (startPos != std::string::npos) return this->response.substr(startPos + 4);

    return this->response;
}