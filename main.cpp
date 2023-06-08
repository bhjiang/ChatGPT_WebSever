#include "server.h"
#include "static_handler.h"

int main() {
	Server server(80);
	Handler *handler=new StaticHandler(".");
	server.add_handler("/index.html", handler);
	server.add_handler("/images/KTV.jpg", handler);
	server.add_handler("/images/太古仓.jpg", handler);
	server.start();
	delete handler;
	server.stop();
    	return 0;
}

