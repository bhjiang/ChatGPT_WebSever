#include "server.h"
#include "static_handler.h"
#include "handler.h"
#include <fstream>
#include <sstream>

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
	
	server.start();
	server.stop();
    	return 0;
}

