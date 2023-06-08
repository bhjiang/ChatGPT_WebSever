#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include "request.h"
#include "response.h"

class Handler {
public:
    virtual void handle(Request& req, Response& res) = 0;
};

#endif // HANDLER_H

