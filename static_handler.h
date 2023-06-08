#ifndef STATIC_HANDLER_H
#define STATIC_HANDLER_H

#include <string>
#include "handler.h"

class StaticHandler : public Handler {
public:
    StaticHandler(std::string root_dir);
    void handle(Request& req, Response& res) override;
private:
    std::string m_root_dir;
    std::string get_content_type(std::string path);
};

#endif // STATIC_HANDLER_H

