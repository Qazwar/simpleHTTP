
#include "HTTP.h"
#include "curl/curl.h"
#include <string>

/* namespace for hiding non-member functions */
namespace details {
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
}

/* Performs GET requests */
HTTP get(const std::string& url) {
    CURL* handle = curl_easy_init();
    CURLcode code;
    std::string buf;
    long response;

    if(handle) {
        curl_easy_setopt(handle, CURLOPT_URL, url.c_str()); // the url
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);    // follow redirects
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, details::WriteCallback);   // string conversion
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, &buf);  // write data to string
        code = curl_easy_perform(handle);   // perform the GET request and get the data
        curl_easy_getinfo (handle , CURLINFO_RESPONSE_CODE, &response); // get the response code
        curl_easy_cleanup(handle);  // clean up

        HTTP d;
        d.code = response;
        d.data = buf;

        return d;
    }
}

/* Performs POST requests */
HTTP post(const std::string& url, const std::string& data) {
    CURL* handle = curl_easy_init();
    CURLcode code;
    std::string buf;
    long response;

    if(handle) {
        curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);    // follow redirects
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, details::WriteCallback);   // string conversion
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, &buf);  // write the POST response to a string
        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, data.c_str()); // set the data to send
        code = curl_easy_perform(handle);   // perform the POST code and get the data
        curl_easy_getinfo (handle , CURLINFO_RESPONSE_CODE, &response); // get the response code
        curl_easy_cleanup(handle);  // clean up

        HTTP d;
        d.code = response;
        d.data = buf;

        return d;
    }
}
