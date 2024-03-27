#include "server.h"
#include "static_handler.h"
#include "login_handler.h"
#include "handler.h"
#include "register_handler.h"

int main() {
	Server server(80);

	// mysql数据库配置
	std::string host="localhost";
	std::string user="bhjiang";
	std::string password="321654";
	std::string datebase="bh";

	// 静态文件根目录
	std::string static_root_dir="/home/bhjiang/bhjiang.github.io/root";
	server.add_handler("", new StaticHandler(static_root_dir));

	// 增加新的handler
	// server.add_handler("login", new LoginHandler(host,user,password,datebase));
	server.add_handler("register_cgi", new RegisterHandler(host,user,password,datebase));
	
	server.start();
	server.stop();
    return 0;
}

