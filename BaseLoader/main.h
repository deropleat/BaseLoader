#pragma once
#define CURL_STATICLIB

#define _NOTIFY_
#define _EXIT_

#ifdef _NOTIFY_
#define NOTIFY(data) std::cout << data << std::endl;
#else
#define NOTIFY(data) {}
#endif

#ifdef _EXIT_
#define EXIT(code, msg) { \
	NOTIFY(msg) \
	system("pause"); \
	return code; \
	}
#else
#define EXIT(code, msg) { \
	NOTIFY(msg) \
	return code; \
	}
#endif

#include <iostream>
#include <thread>
#include <fstream>
#include <filesystem>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include <shlwapi.h>
#include <shlobj.h>