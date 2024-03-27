#include <iostream>
#include <sstream>
#include "request.h"

Request::Request(std::string request)
{

    std::istringstream ss(request);
    std::string line;

    // 解析请求行
    std::getline(ss, line);
    size_t pos = line.find(" ");
    method = line.substr(0, pos);
    line.erase(0, pos + 1);
    pos = line.find(" ");
    path = line.substr(0, pos);
    line.erase(0, pos + 1);
    version = line;

    // 解析请求头
    while (std::getline(ss, line) && line != "\r") {
        pos = line.find(": ");
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 2);
            headers[key] = value;
        }
    }

    // 获取请求体
    std::getline(ss, body);

}

std::string Request::get_method() {
    return method;
}

std::string Request::get_path() {
    return path;
}
std::string Request::get_version() {
    return version;
}
std::string Request::get_body() {
    return body;
}

std::string Request::get_header(std::string key) {
    auto it = headers.find(key);
    if (it != headers.end()) {
        return it->second;
    } else {
        return "";
    }
}

std::unordered_map<std::string, std::string> Request::get_post_data() {
    std::unordered_map<std::string, std::string> post_data;
    std::istringstream ss(body);
    std::string key_value;

    while (std::getline(ss, key_value, '&')) {
        size_t pos = key_value.find('=');
        if (pos != std::string::npos) {
            std::string key = key_value.substr(0, pos);
            std::string value = key_value.substr(pos + 1);
            post_data[key] = value;
        }
    }
    return post_data;
}



