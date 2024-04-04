#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <unordered_map>

class Request {
public:
    void set_method(std::string method_);
    void set_path(std::string path_);
    void set_version(std::string version_);
    void set_header(std::string key_, std::string value_);
    void set_param(std::string key_, std::string value_);

    std::string get_method();
    std::string get_path();
    std::string get_version();
    bool get_header(std::string key_,std::string &value_);
    bool get_param(std::string key_,std::string &value_);
private:
    std::string method;
    std::string path;
    std::string version;
    std::unordered_map<std::string, std::string> header;
    std::unordered_map<std::string, std::string> param;
};

#endif // REQUEST_H

