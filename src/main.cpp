#include "server.h"
#include "static_handler.h"
#include "handler.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>

class DefaultHandler: public Handler {
public:
	DefaultHandler(std::string filename);
	void handle(Request& req, Response& res) override;
private:
    std::string m_filename;
};

DefaultHandler::DefaultHandler(std::string filename){
	m_filename=filename;
}

void DefaultHandler::handle(Request& req, Response& res){
    // Read file contents
    std::ifstream file(m_filename);
    if (!file.is_open()) {
        res.set_status_code(500);
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
	
    // Set response headers
    res.set_status_code(200);
    res.set_header("Content-Type", "text/html");
    res.set_body(content);
}

class PostHandler : public Handler {
public:
	PostHandler(std::string host, std::string user, std::string password, std::string database);
	void handle(Request& req, Response& res) override;
private:
	std::string m_host;
	std::string m_user;
	std::string m_password;
};

PostHandler::PostHandler(std::string host, std::string user, std::string password, std::string database)
{
	mysql = mysql_init(NULL);
	if (!mysql_real_connect(mysql, host, user, password, database, 0, NULL, 0)) {
		std::cout << "Failed to connect to database." << std::endl;
	}
}

void PostHandler::handle(Request& req, Respond& res)
{
    
    // 解析post数据，获取Name, Email和Message字段的值
    std::string name, email, message;
    size_t pos = req.find("Name=");
    if (pos != std::string::npos) {
        name = req.substr(pos + 5);
        pos = name.find("&");
        if (pos != std::string::npos) {
            name = name.substr(0, pos);
        }
    }
    pos = req.find("Email=");
    if (pos != std::string::npos) {
        email = req.substr(pos + 6);
        pos = email.find("&");
        if (pos != std::string::npos) {
            email = email.substr(0, pos);
        }
    }
    pos = req.find("Message=");
    if (pos != std::string::npos) {
        message = req.substr(pos + 8);
    }

    // 将数据写入mysql数据库
    if (mysql) {
        std::string query = "INSERT INTO messages (name, email, message) VALUES ('" + name + "', '" + email + "', '" + message + "')";
        mysql_query(mysql, query.c_str());
        std::cout << "Data inserted successfully." << std::endl;
    }
    else {
        res.set_status_code(500);
        std::cout << "Failed to connect to database." << std::endl;
    }
}

int main() {
	Server server(80);
	StaticHandler* statichandler=new StaticHandler("/home/bhjiang/bhjiang.github.io");
	
	server.add_handler("/", new DefaultHandler("/home/bhjiang/bhjiang.github.io/index.html"));
	
	server.add_handler("/index.html", statichandler);
	server.add_handler("/script.js", statichandler);
	server.add_handler("/style.css", statichandler);
	server.add_handler("/images/KTV.jpg", statichandler);
	server.add_handler("/images/GuangzhouSouth.jpg", statichandler);
	server.add_handler("/images/linnanyinxiang.jpg", statichandler);
	server.add_handler("/images/higthway.jpg", statichandler);
	server.add_handler("/images/taigucang.jpg", statichandler);
	server.add_handler("/images/flower.jpg", statichandler);
	server.add_handler("/images/JsonZhang.jpg", statichandler);
	server.add_handler("/images/changlong.jpg", statichandler);

	server.add_handler("/submit.php", new PostHandler("119.91.222.11","root","","web");
	
	server.start();
	server.stop();
    return 0;
}

