#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <map>

class Response {
public:
    std::string to_string();
    int get_status_code();
    std::string get_header(std::string name);
    std::string get_body();
    void set_status_code(int code);
    void set_header(std::string name, std::string value);
    void set_body(std::string body);
private:
    int m_status_code;
    std::map<std::string, std::string> m_headers;
    std::string m_body;
};

#endif // RESPONSE_H

