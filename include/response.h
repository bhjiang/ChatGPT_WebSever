#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <map>

class Response {
public:
    std::string to_response();
    void set_status_code(int code);
    void set_header(std::string name, std::string value);
    void set_body(std::string body);
private:
    int status_code;
    std::map<std::string, std::string> headers;
    std::string body;
};

#endif // RESPONSE_H

