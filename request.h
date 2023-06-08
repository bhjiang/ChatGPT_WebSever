#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <map>

class Request {
public:
    Request(std::string method, std::string path, std::string body);
    std::string get_method();
    std::string get_path();
    std::string get_body();
    std::string get_header(std::string name);
    void set_header(std::string name, std::string value);
private:
    std::string m_method;
    std::string m_path;
    std::string m_body;
    std::map<std::string, std::string> m_headers;
};

#endif // REQUEST_H

