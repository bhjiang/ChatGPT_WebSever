#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H

#include <string>
#include "handler.h"

class LoginHandler : public Handler {
public:
    LoginHandler(std::string host_, std::string user_, std::string password_, std::string database_);
    void handle(Request& req, Response& res) override;
private:
	std::string host;
	std::string user;
	std::string password;
    std::string database;
};

#endif

