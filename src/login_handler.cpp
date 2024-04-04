#include "login_handler.h"
#include <mysql/mysql.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <unordered_map>

LoginHandler::LoginHandler(std::string host_, std::string user_, std::string password_, std::string database_)
{
	host=host_;
	user=user_;
	password=password_;
    database=database_;
}

void LoginHandler::handle(Request& req, Response& res)
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
		std::cout << "Failed to connect to database." << std::endl;
        return;
	}

    std::string user,password;

    if(req.get_param("user",user)&&req.get_param("password",password))
    {
        std::string query = "SELECT * FROM user WHERE username='"+user+"' AND passwd='"+password+"';";
        std::cout<<query<<std::endl;

        std::string path;
        if(!mysql_query(con, query.c_str()))
        {
            auto re=mysql_use_result(con);
            auto row = mysql_fetch_row(re);
            if(row)
            {
                path ="/index.html";
            }
            else
            {
                path ="/logError.html";
            }
        }
        else
        {
            path ="/logError.html";
        }

        read_static_file(path, res);
    }
}