#pragma once
#include "requests.h"

class CBase
{
public:
	CBase();
	CBase(std::string = "");

	size_t getContentLength()
	{
		return this->contentLength;
	}

	std::string getResponse();
	std::string getHeader();

	void resolveContentLength(size_t);
private:
	std::string getHeader(std::string);

	size_t contentLength = 0;
	std::string url = "", response = "";
};