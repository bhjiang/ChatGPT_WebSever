#include <iostream>
#include <sstream>
#include "response.h"

std::string Response::to_string() {
    std::stringstream ss;
    ss << "HTTP/1.1 " << m_status_code << " " << "OK" << "\r\n";
    for (auto& header : m_headers) {
        ss << header.first << ": " << header.second << "\r\n";
    }
    ss << "\r\n";
    ss << m_body;
    return ss.str();
}

int Response::get_status_code() {
    return m_status_code;
}

std::string Response::get_header(std::string name) {
    auto it = m_headers.find(name);
    if (it != m_headers.end()) {
        return it->second;
    } else {
        return "";
    }
}

std::string Response::get_body() {
    return m_body;
}

void Response::set_status_code(int code) {
    m_status_code = code;
}

void Response::set_header(std::string name, std::string value) {
    m_headers[name] = value;
}

void Response::set_body(std::string body) {
    m_body = body;
}

