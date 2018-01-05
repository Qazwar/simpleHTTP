/**
 * HTTP.h
 * Purpose: Interface for simpleHTTP
 *
 * @author Encryptio
 * @version 0.10
 */

#ifndef HTTP_HTTP_H
#define HTTP_HTTP_H

#include "curl/curl.h"
#include <string>


//class HTTP {
//
//};

struct HTTP {
    std::string data;
    long code;
};

/** Performs GET requests
 *
 * @param url
 * @return
 */
HTTP get(const std::string& url);

/** Performs POST requests
 *
 * @param url
 * @param data
 * @return
 */
HTTP post(const std::string& url, const std::string& data);


#endif //HTTP_HTTP_H
