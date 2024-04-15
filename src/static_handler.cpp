#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include "static_handler.h"

void StaticHandler::handle(Request& req, Response& res) {
    // Get file path
    std::string url=req.get_path();
    if(url=="/"){
        url="/index.html";
    }
    std::cout<<"url:"<<url<<std::endl;
    // std::string path = root_dir + url;
    // std::cout<<path<<std::endl;
    read_static_file(url, res);
}



