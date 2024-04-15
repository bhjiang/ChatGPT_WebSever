#include "server.h"
#include "static_handler.h"
#include "login_handler.h"
#include "handler.h"
#include "register_handler.h"

int main(int argc, char** argv) {
	int port=argv[1]?atoi(argv[1]):80;
	Server server(port);

	// mysql数据库配置
	std::string host="localhost";
	std::string user="bhjiang";
	std::string password="321654";
	std::string datebase="bh";

	// 静态文件根目录
	std::string root="/home/bhjiang/bhjiang.github.io";
	Handler::root_dir=root;
	// StaticHandler* staticHandler=new StaticHandler();
	// staticHandler->root_dir=root;
	server.add_handler("static", new StaticHandler());

	// 增加新的handler
	server.add_handler("login.cgi", new LoginHandler(host,user,password,datebase));
	server.add_handler("register.cgi", new RegisterHandler(host,user,password,datebase));
	
	server.start();
	server.stop();
    return 0;
}

