#include "register_handler.h"
#include <mysql/mysql.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include "static_handler.h"

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
        // res.set_status_code(500);
        std::cout << "Mysql error" << std::endl;
        return;
    }
	if (!mysql_real_connect(con, host.c_str(), user.c_str(), password.c_str(), database.c_str(), 3306, NULL, 0)) {
        // res.set_status_code(500);
		std::cout << "Failed to connect to database." << std::endl;
        return;
	}

    std::string user,password;

    if(req.get_param("user",user)&&req.get_param("password",password))
    {
        std::string query = "insert into user_profile (user, password) VALUES ('";
        query=query + user + "', '" + password + "');";
        std::cout<<query<<std::endl;

        std::string path;
        if(!mysql_query(con, query.c_str()))
        {
            path ="/login.html"; // 成功注册后跳转到登录页面
            std::cout << "Register success" << std::endl;
        }
        else
        {
            path ="/registerError.html"; // 注册失败
        }

        read_static_file(path, res);
    }
    else
    {
        std::cout<<"No user or password"<<std::endl;
        return;
    }


}