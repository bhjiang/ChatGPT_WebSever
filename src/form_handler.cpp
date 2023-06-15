#include "form_handler.h"
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <stdlib.h>

void FormHandler::handle(Request& req, Response& res) {
	system("sudo php /home/bhjiang/bhjiang.github.io/submit.php");
}

