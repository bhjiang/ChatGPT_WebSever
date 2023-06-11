#include <iostream>
#include <sstream>
#include "request.h"

Request::Request(std::string method, std::string path, std::string body) :
    m_method(method),
    m_path(path),
    m_body(body)
{}

std::string Request::get_method() {
    return m_method;
}

std::string Request::get_path() {
    return m_path;
}

std::string Request::get_body() {
    return m_body;
}

std::string Request::get_header(std::string name) {
    auto it = m_headers.find(name);
    if (it != m_headers.end()) {
        return it->second;
    } else {
        return "";
    }
}

void Request::set_header(std::string name, std::string value) {
    m_headers[name] = value;
}

