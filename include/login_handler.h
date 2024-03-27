#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H

#include <string>
#include "handler.h"

class LoginHandler : public Handler {
public:
    LoginHandler(std::string host, std::string user, std::string password, std::string database);
    void handle(Request& req, Response& res) override;
private:
	std::string m_host;
	std::string m_user;
	std::string m_password;
    std::string m_database;
};

#endif

