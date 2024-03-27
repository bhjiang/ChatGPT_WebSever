#ifndef REGISTER_HANDLER_H
#define REGISTER_HANDLER_H

#include <string>
#include "handler.h"

class RegisterHandler : public Handler {
public:
    RegisterHandler(std::string _host, std::string _user, std::string _password, std::string _database);
    void handle(Request& req, Response& res) override;
private:
	std::string host;
	std::string user;
	std::string password;
    std::string database;
};

#endif