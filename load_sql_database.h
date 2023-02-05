#pragma once

#include "sql_headers.h"
#include <bitset>
#include <coroutine>

#define sql_database "tdameritrade"
#define sql_table_company_fundamental "company_fundamental"
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
	dbStatus check_company_fundamental();
	dbStatus check_td_price_history_day();
	dbStatus check_td_price_history_minute();

	dbStatus check_table(const std::string &table_name);

private:
	dbStatus sql_table_status = 0x00;

	sql::Driver *sql_driver;
	sql::Connection *sql_connection;
	sql::PreparedStatement *sql_statement;
	sql::ResultSet *sql_result;

	std::string makeTable_company_fundamental = "CREATE TABLE tdameritrade.company_fundamental ( "
												"ID int unsigned NOT NULL AUTO_INCREMENT, "
												"cusip varchar(100) NOT NULL, "
												"symbol varchar(50) NOT NULL, "
												"description varchar(255) NOT NULL, "
												"exchange varchar(50) NOT NULL, "
												"assetType varchar(50) NOT NULL, "
												"high52 double NOT NULL, "
												"low52 double NOT NULL, "
												"dividendAmount double NOT NULL, "
												"dividendYield double NOT NULL, "
												"dividendDate varchar(255) NOT NULL, "
												"peRatio double NOT NULL, "
												"pegRatio double NOT NULL, "
												"pbRatio double NOT NULL, "
												"prRatio double NOT NULL, "
												"pcfRatio double NOT NULL, "
												"grossMarginTTM double NOT NULL, "
												"grossMarginMRQ double NOT NULL, "
												"netProfitMarginTTM double NOT NULL, "
												"netProfitMarginMRQ double NOT NULL, "
												"operatingMarginTTM double NOT NULL, "
												"operatingMarginMRQ double NOT NULL, "
												"returnOnEquity double NOT NULL, "
												"returnOnAssets double NOT NULL, "
												"returnOnInvestment double NOT NULL, "
												"quickRatio double NOT NULL, "
												"currentRatio double NOT NULL, "
												"interestCoverage double NOT NULL, "
												"totalDebtToCapital double NOT NULL, "
												"ltDebtToEquity double NOT NULL, "
												"totalDebtToEquity double NOT NULL, "
												"epsTTM double NOT NULL, "
												"epsChangePercentTTM double NOT NULL, "
												"epsChangeYear double NOT NULL, "
												"epsChange double NOT NULL, "
												"revChangeYear double NOT NULL, "
												"revChangeTTM double NOT NULL, "
												"revChangeIn double NOT NULL, "
												"sharesOutstanding double NOT NULL, "
												"marketCapFloat double NOT NULL, "
												"marketCap double NOT NULL, "
												"bookValuePerShare double NOT NULL, "
												"shortIntToFloat double NOT NULL, "
												"shortIntDayToCover double NOT NULL, "
												"divGrowthRate3Year double NOT NULL, "
												"dividendPayAmount double NOT NULL, "
												"dividendPayDate varchar(255) NOT NULL, "
												"beta double NOT NULL, "
												"vol1DayAvg double NOT NULL, "
												"vol10DayAvg double NOT NULL, "
												"vol3MonthAvg double NOT NULL, "
												"PRIMARY KEY (`ID`), "
												"UNIQUE KEY `ID` (`ID`), "
												"UNIQUE KEY `symbol` (`symbol`) "
												") ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;";
	
	std::string makeTable_td_price_history_day = "CREATE TABLE tdameritrade.td_price_history_day ( "
												 "ID int unsigned NOT NULL AUTO_INCREMENT, "
												 "symbol varchar(50) NOT NULL, "
												 "open double NOT NULL, "
												 "high double NOT NULL, "
												 "low double NOT NULL, "
												 "close double NOT NULL, "
												 "volume bigint unsigned NOT NULL, "
												 "datetime bigint unsigned NOT NULL, "
												 "PRIMARY KEY (ID), "
												 "FOREIGN KEY (symbol) REFERENCES company_fundamental (symbol), "
												 "UNIQUE KEY ID (ID) "
												 ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;";

	std::string makeTable_td_price_history_minute = "CREATE TABLE tdameritrade.td_price_history_minute ( "
													"ID int unsigned NOT NULL AUTO_INCREMENT, "
													"symbol varchar(50) NOT NULL, "
													"open double NOT NULL, "
													"high double NOT NULL, "
													"low double NOT NULL, "
													"close double NOT NULL, "
													"volume bigint unsigned NOT NULL, "
													"datetime bigint unsigned NOT NULL, "
													"PRIMARY KEY (ID), "
													"FOREIGN KEY (symbol) REFERENCES company_fundamental (symbol), "
													"UNIQUE KEY ID (ID) "
													") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;";
};
