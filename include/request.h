#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <unordered_map>

class Request {
public:
    Request(std::string buf);
    std::string get_method();
    std::string get_path();
    std::string get_version();
    std::string get_body();
    std::string get_header(std::string key);
    std::unordered_map<std::string, std::string> get_post_data();
private:
    std::string method;
    std::string path;
    std::string version;
    std::string body;
    std::unordered_map<std::string, std::string> headers;
};

#endif // REQUEST_H

