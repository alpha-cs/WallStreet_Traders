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
}typedef Fundamental;


class sql_data_logger
{
public:
	sql_data_logger();
	~sql_data_logger();
	void fundamentalsHandler(const std::string metadata_symbol, const std::string& response);
	void fundamentalsLogger(Fundamental& metadata);

private:
	sql::Driver* sql_driver;
	sql::Connection* sql_connection;
	sql::PreparedStatement* sql_statement;
	sql::ResultSet* sql_result;

	Fundamental metadata;
	const std::string fundamentalQuery = "INSERT INTO `tdameritrade`.`company_fundamental` (`cusip`, `symbol`, `description`, `exchange`, `assetType`, `high52`, `low52`, `dividendAmount`, `dividendYield`, `dividendDate`, `peRatio`, `pegRatio`, `pbRatio`, `prRatio`, `pcfRatio`, `grossMarginTTM`, `grossMarginMRQ`, `netProfitMarginTTM`, `netProfitMarginMRQ`, `operatingMarginTTM`, `operatingMarginMRQ`, `returnOnEquity`, `returnOnAssets`, `returnOnInvestment`, `quickRatio`, `currentRatio`, `interestCoverage`, `totalDebtToCapital`, `ltDebtToEquity`, `totalDebtToEquity`, `epsTTM`, `epsChangePercentTTM`, `epsChangeYear`, `epsChange`, `revChangeYear`, `revChangeTTM`, `revChangeIn`, `sharesOutstanding`, `marketCapFloat`, `marketCap`, `bookValuePerShare`, `shortIntToFloat`, `shortIntDayToCover`, `divGrowthRate3Year`, `dividendPayAmount`, `dividendPayDate`, `beta`, `vol1DayAvg`, `vol10DayAvg`, `vol3MonthAvg`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
};