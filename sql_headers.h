#pragma once

#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/prepared_statement.h"

// for demonstration only. never save password in the code!
// Also I couldnt be bothered to implemetn the key loader here. But you can and submit a pull request.
#define mysql_Host "localhost"     // server host
#define mysql_User "root"          // server user
#define mysql_Password "5662"      // server password | This is my name in number format. :)
#define mysql_Password_Fail "0000" // Fail Connection to database\

enum sql_tdameritrade_table
{
	company_fundamental = 0,
	td_price_history_day,
	td_price_history_minute,
	sizeof_sql_tdameritrade_table
};