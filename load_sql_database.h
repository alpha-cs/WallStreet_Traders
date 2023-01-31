#pragma once

#include "sql_headers.h"
#include <bitset>

#define sql_database "tdameritrade"
#define sql_table_company_info "company_info"
#define sql_table_td_price_history_day "td_price_history_day"
#define sql_table_td_price_history_minute "td_price_history_minute"

typedef uint8_t dbStatus;

class load_sql_database
{
public:
    load_sql_database();
    ~load_sql_database();
    void make_sql_table();
    dbStatus check_sql_tables();
    dbStatus check_company_info();
    dbStatus check_td_price_history_day();
    dbStatus check_td_price_history_minute();

    dbStatus check_table(const std::string& table_name);
	

private:
    dbStatus sql_table_status = 0x00;
	
    sql::Driver *sql_driver;
    sql::Connection *sql_connection;
    sql::PreparedStatement *sql_statement;
    sql::ResultSet *sql_result;

    std::string maketable_company_info = "CREATE TABLE tdameritrade.company_info ( "
        "`ID` int unsigned NOT NULL AUTO_INCREMENT, "
        "`Name` varchar(100) NOT NULL, "
        "`Symbol` varchar(50) NOT NULL, "
        "`MarketCap` varchar(25) DEFAULT NULL, "
        "`Flag` tinyint unsigned NOT NULL, "
        "PRIMARY KEY (`ID`), "
        "UNIQUE KEY `Name` (`Name`), "
        "UNIQUE KEY `Ticker` (`Symbol`), "
        "UNIQUE KEY `ID` (`ID`) "
        ") ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;";

    std::string maketable_td_price_history_day = "CREATE TABLE tdameritrade.td_price_history_day ( "
        "ID int unsigned NOT NULL AUTO_INCREMENT, "
        "Symbol varchar(50) NOT NULL, "
        "Open double NOT NULL, "
        "High double NOT NULL, "
        "Low double NOT NULL, "
        "Close double NOT NULL, "
        "Volume bigint unsigned NOT NULL, "
        "Datetime bigint unsigned NOT NULL, "
        "PRIMARY KEY (ID), "
        "FOREIGN KEY (Symbol) REFERENCES company_info (Symbol), "
        "UNIQUE KEY ID (ID) "
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;";

    std::string maketable_td_price_history_minute = "CREATE TABLE tdameritrade.td_price_history_minute ( "
        "ID int unsigned NOT NULL AUTO_INCREMENT, "
        "Symbol varchar(50) NOT NULL, "
        "Open double NOT NULL, "
        "High double NOT NULL, "
        "Low double NOT NULL, "
        "Close double NOT NULL, "
        "Volume bigint unsigned NOT NULL, "
        "Datetime bigint unsigned NOT NULL, "
        "PRIMARY KEY (ID), "
        "FOREIGN KEY (Symbol) REFERENCES company_info (Symbol), "
        "UNIQUE KEY ID (ID) "
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;";

};
