#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include "request.h"
#include "response.h"

class Handler {
public:
    virtual void handle(Request& req, Response& res) = 0;
    void read_static_file(std::string path, Response& res);
    static std::string root_dir;
private:
    std::string get_content_type(std::string path);
};

#endif // HANDLER_H

