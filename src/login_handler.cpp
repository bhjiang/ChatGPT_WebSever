#include "login_handler.h"
#include <mysql/mysql.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <unordered_map>

LoginHandler::LoginHandler(std::string host, std::string user, std::string password, std::string database)
{
	m_host=host;
	m_user=user;
	m_password=password;
    m_database=database;
}

void LoginHandler::handle(Request& req, Response& res)
{
    MYSQL *con = NULL;
    con = mysql_init(con);

    if (con == NULL)
    {
        res.set_status_code(500);
        std::cout << "Mysql error" << std::endl;
        exit(1);
    }
	if (!mysql_real_connect(con, m_host.c_str(), m_user.c_str(), m_password.c_str(), m_database.c_str(), 3306, NULL, 0)) {
		std::cout << "Failed to connect to database." << std::endl;
        exit(1);
	}

    auto post_data=req.get_post_data();
    std::string query = "INSERT INTO messages ((username, passwd) VALUES ('" + post_data["username"] + post_data["passwd"] + "')";
    mysql_query(con, query.c_str());
    // std::cout << "Data inserted successfully." << std::endl;
}