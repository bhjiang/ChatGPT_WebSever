#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include "static_handler.h"

StaticHandler::StaticHandler(std::string root_dir) :
    m_root_dir(root_dir)
{}

void StaticHandler::handle(Request& req, Response& res) {
    // Get file path
    std::string path = m_root_dir + req.get_path();
	//std::cout<<path<<std::endl;
	
    // Check if file exists
    struct stat st;
    if (stat(path.c_str(), &st) != 0 || !(st.st_mode & S_IFREG)) {
        res.set_status_code(404);
        return;
    }

    // Read file contents
    std::ifstream file(path);
    if (!file.is_open()) {
        res.set_status_code(500);
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    // Set response headers
    res.set_status_code(200);
    res.set_header("Content-Type", get_content_type(path));
    res.set_body(content);
}

std::string StaticHandler::get_content_type(std::string path) {
    // Get file extension
    size_t pos = path.rfind(".");
    if (pos == std::string::npos) {
        return "application/octet-stream";
    }
    std::string ext = path.substr(pos + 1);

    // Map extension to content type
    if (ext == "html" || ext == "htm") {
        return "text/html";
    } else if (ext == "css") {
        return "text/css";
    } else if (ext == "js") {
        return "application/javascript";
    } else if (ext == "json") {
        return "application/json";
    } else if (ext == "xml") {
        return "application/xml";
    } else if (ext == "gif") {
        return "image/gif";
    } else if (ext == "jpeg" || ext == "jpg") {
        return "image/jpeg";
    } else if (ext == "png") {
        return "image/png";
    } else if (ext == "svg") {
        return "image/svg+xml";
    } else if (ext == "pdf") {
        return "application/pdf";
    } else {
        return "application/octet-stream";
    }
}

