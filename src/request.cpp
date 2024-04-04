#include <iostream>
#include <sstream>
#include "request.h"

void Request::set_method(std::string method_)
{
    method=method_;
}
void Request::set_path(std::string path_)
{
    path=path_;
}
void Request::set_version(std::string version_)
{
    version=version_;
}
void Request::set_header(std::string key_, std::string value_)
{
    header[key_]=value_;
}
void Request::set_param(std::string key_, std::string value_)
{
    param[key_]=value_;
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
bool Request::get_header(std::string key_,std::string &value_)
{
    if(!header.count(key_))
        return false;
    value_=header[key_];
    return true;
}
bool Request::get_param(std::string key_,std::string &value_)
{
    if(!param.count(key_))
        return false;
    value_=param[key_];
    return true;
}






