#ifndef FORM_HANDLER_H
#define FORM_HANDLER_H

#include "handler.h"

class FormHandler : public Handler {
public:
    void handle(Request& req, Response& res) override;
};

#endif // FORM_HANDLER_H

