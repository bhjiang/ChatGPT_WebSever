#include "register_handler.h"
#include <mysql/mysql.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <fstream>

RegisterHandler::RegisterHandler(std::string _host, std::string _user, std::string _password, std::string _database)
{
	host=_host;
	user=_user;
	password=_password;
    database=_database;
}

void RegisterHandler::handle(Request& req, Response& res)
{
    MYSQL *con = NULL;
    con = mysql_init(con);

    if (con == NULL)
    {
        res.set_status_code(500);
        std::cout << "Mysql error" << std::endl;
        exit(1);
    }
	if (!mysql_real_connect(con, host.c_str(), user.c_str(), password.c_str(), database.c_str(), 3306, NULL, 0)) {
		std::cout << "Failed to connect to database." << std::endl;
        exit(1);
	}

    auto post_data=req.get_post_data();
    std::cout<<post_data["user"]<<" "<<post_data["password"]<<std::endl;

    std::string query = "INSERT ignore INTO user (username, passwd) VALUES ('";
    query=query + post_data["user"] + "', '" + post_data["password"] + "');";
    std::cout<<query<<std::endl;

    std::string root_dir="/home/bhjiang/bhjiang.github.io/root";
    if(!mysql_query(con, query.c_str()))
    {
        std::string path="/log.html";
        std::ifstream file(root_dir + path);
        if (!file.is_open()) {
            res.set_status_code(500);
            return;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        res.set_body(buffer.str());
    }
    else
    {
        std::string path="/registerError.html";
        std::ifstream file(root_dir + path);
        if (!file.is_open()) {
            res.set_status_code(500);
            return;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        res.set_body(buffer.str());
    }
}