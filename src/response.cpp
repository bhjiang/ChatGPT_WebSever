#include <iostream>
#include <sstream>
#include "response.h"

std::string Response::to_response() {
    std::stringstream ss;
    ss << "HTTP/1.1 " << status_code << " " << "OK" << "\r\n";
    for (auto& header : headers) {
        ss << header.first << ": " << header.second << "\r\n";
    }
    ss << "\r\n";
    ss << body;
    return ss.str();
}

void Response::set_status_code(int code) {
    status_code = code;
}

void Response::set_header(std::string key, std::string value) {
    headers[key] = value;
}

void Response::set_body(std::string _body) {
    body = _body;
}
