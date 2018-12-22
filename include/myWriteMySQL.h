#ifndef _MYWRITEMYSQL_H_
#define _MYWRITEMYSQL_H_

/* Standard C++ includes */
#include <stdlib.h>
#include <string>
#include <iostream>

/* mysql includes */
#include <jdbc/mysql_driver.h>
#include "jdbc/mysql_connection.h"
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>

bool myWriteMySQL(const std::string &cuuid, const std::string &cmatrix, const std::string &ctype);

#endif