#include "requests.h"

namespace requests
{
    static size_t write_data(char* ptr, size_t size, size_t nmemb, std::string* data)
    {
        if (data)
        {
            data->append(ptr, size * nmemb);
            return size * nmemb;
        }
        return 0;
    }

    std::string SendHTTP_GET(std::string url)
    {
        CURL* curl_handle = curl_easy_init();

        if (curl_handle)
        {
            std::string data;

            curl_easy_setopt(curl_handle, CURLOPT_URL, url);
            curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.1; rv:16.0) Gecko/20100101 Firefox/16.0");
            curl_easy_setopt(curl_handle, CURLOPT_HEADER, 1);

            std::string result;
            curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &result);

            if (!data.empty())
            {
                curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, data.c_str());
                curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, data.length());
            }

            CURLcode res = curl_easy_perform(curl_handle);
            curl_easy_cleanup(curl_handle);

            return result;
        }
    }
}