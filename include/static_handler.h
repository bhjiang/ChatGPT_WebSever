#ifndef STATIC_HANDLER_H
#define STATIC_HANDLER_H

#include <string>
#include "handler.h"

class StaticHandler : public Handler {
public:
    void handle(Request& req, Response& res) override;
};

#endif // STATIC_HANDLER_H

