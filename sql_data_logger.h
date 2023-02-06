#pragma once

#include <iostream>
#include <string>
#include "sql_headers.h"
#include <json/json.h>f

struct Fundamental {
	std::string cusip;
	std::string symbol;
	std::string description;
	std::string exchange;
	std::string assetType;
	double high52;
	double low52;
	double dividendAmount;
	double dividendYield;
	std::string dividendDate;
	double peRatio;
	double pegRatio;
	double pbRatio;
	double prRatio;
	double pcfRatio;
	double grossMarginTTM;
	double grossMarginMRQ;
	double netProfitMarginTTM;
	double netProfitMarginMRQ;
	double operatingMarginTTM;
	double operatingMarginMRQ;
	double returnOnEquity;
	double returnOnAssets;
	double returnOnInvestment;
	double quickRatio;
	double currentRatio;
	double interestCoverage;
	double totalDebtToCapital;
	double ltDebtToEquity;
	double totalDebtToEquity;
	double epsTTM;
	double epsChangePercentTTM;
	double epsChangeYear;
	double epsChange;
	double revChangeYear;
	double revChangeTTM;
	double revChangeIn;
	double sharesOutstanding;
	double marketCapFloat;
	double marketCap;
	double bookValuePerShare;
	double shortIntToFloat;
	double shortIntDayToCover;
	double divGrowthRate3Year;
	double dividendPayAmount;
	std::string dividendPayDate;
	double beta;
	double vol1DayAvg;
	double vol10DayAvg;
	double vol3MonthAvg;
};


class sql_data_logger
{
public:
	sql_data_logger();
	~sql_data_logger();
	void store_data_to_db(const std::string& response);
private:
	sql::Driver* sql_driver;
	sql::Connection* sql_connection;
	sql::PreparedStatement* sql_statement;
	sql::ResultSet* sql_result;

	Fundamental metadata;
};