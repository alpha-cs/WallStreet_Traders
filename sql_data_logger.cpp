#include "sql_data_logger.h"

sql_data_logger::sql_data_logger()
{
	try
	{
		this->sql_driver = get_driver_instance();
		this->sql_connection = sql_driver->connect(mysql_Host, mysql_User, mysql_Password);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		exit(1);
	}
}

sql_data_logger::~sql_data_logger()
{
	delete sql_result;
	delete sql_statement;
	delete sql_connection;
}

void sql_data_logger::store_data_to_db(const std::string& response)
{
	// Parse JSON response
	Json::Value root;
	Json::Reader reader;
	if (!reader.parse(response, root)) {
		std::cerr << "Failed to parse response: " << reader.getFormattedErrorMessages() << std::endl;
		return;
	}

	// Extract values from JSON response	
	metadata.cusip = root["META"]["cusip"].asString();
	metadata.symbol = root["META"]["symbol"].asString();
	metadata.description = root["META"]["description"].asString();
	metadata.exchange = root["META"]["exchange"].asString();
	metadata.assetType = root["META"]["assetType"].asString();
	metadata.high52 = root["META"]["fundamental"]["high52"].asDouble();
	metadata.low52 = root["META"]["fundamental"]["low52"].asDouble();
	metadata.dividendAmount = root["META"]["fundamental"]["dividendAmount"].asDouble();
	metadata.dividendYield = root["META"]["fundamental"]["dividendYield"].asDouble();
	metadata.dividendDate = root["META"]["fundamental"]["dividendDate"].asString();
	metadata.peRatio = root["META"]["fundamental"]["peRatio"].asDouble();
	metadata.pegRatio = root["META"]["fundamental"]["pegRatio"].asDouble();
	metadata.pbRatio = root["META"]["fundamental"]["pbRatio"].asDouble();
	metadata.prRatio = root["META"]["fundamental"]["prRatio"].asDouble();
	metadata.pcfRatio = root["META"]["fundamental"]["pcfRatio"].asDouble();
	metadata.grossMarginTTM = root["META"]["fundamental"]["grossMarginTTM"].asDouble();
	metadata.grossMarginMRQ = root["META"]["fundamental"]["grossMarginMRQ"].asDouble();
	metadata.netProfitMarginTTM = root["META"]["fundamental"]["netProfitMarginTTM"].asDouble();
	metadata.netProfitMarginMRQ = root["META"]["fundamental"]["netProfitMarginMRQ"].asDouble();
	metadata.operatingMarginTTM = root["META"]["fundamental"]["operatingMarginTTM"].asDouble();
	metadata.operatingMarginMRQ = root["META"]["fundamental"]["operatingMarginMRQ"].asDouble();
	metadata.returnOnEquity = root["META"]["fundamental"]["returnOnEquity"].asDouble();
	metadata.returnOnAssets = root["META"]["fundamental"]["returnOnAssets"].asDouble();
	metadata.returnOnInvestment = root["META"]["fundamental"]["returnOnInvestment"].asDouble();
	metadata.quickRatio = root["META"]["fundamental"]["quickRatio"].asDouble();
	metadata.currentRatio = root["META"]["fundamental"]["currentRatio"].asDouble();
	metadata.interestCoverage = root["META"]["fundamental"]["interestCoverage"].asDouble();
	metadata.totalDebtToCapital = root["META"]["fundamental"]["totalDebtToCapital"].asDouble();
	metadata.ltDebtToEquity = root["META"]["fundamental"]["ltDebtToEquity"].asDouble();
	metadata.totalDebtToEquity = root["META"]["fundamental"]["totalDebtToEquity"].asDouble();
	metadata.epsTTM = root["META"]["fundamental"]["epsTTM"].asDouble();
	metadata.epsChangePercentTTM = root["META"]["fundamental"]["epsChangePercentTTM"].asDouble();
	metadata.epsChangeYear = root["META"]["fundamental"]["epsChangeYear"].asDouble();
	metadata.epsChange = root["META"]["fundamental"]["epsChange"].asDouble();
	metadata.revChangeYear = root["META"]["fundamental"]["revChangeYear"].asDouble();
	metadata.revChangeTTM = root["META"]["fundamental"]["revChangeTTM"].asDouble();
	metadata.revChangeIn = root["META"]["fundamental"]["revChangeIn"].asDouble();
	metadata.sharesOutstanding = root["META"]["fundamental"]["sharesOutstanding"].asDouble();
	metadata.marketCapFloat = root["META"]["fundamental"]["marketCapFloat"].asDouble();
	metadata.marketCap = root["META"]["fundamental"]["marketCap"].asDouble();
	metadata.bookValuePerShare = root["META"]["fundamental"]["bookValuePerShare"].asDouble();
	metadata.shortIntToFloat = root["META"]["fundamental"]["shortIntToFloat"].asDouble();
	metadata.shortIntDayToCover = root["META"]["fundamental"]["shortIntDayToCover"].asDouble();
	metadata.divGrowthRate3Year = root["META"]["fundamental"]["divGrowthRate3Year"].asDouble();
	metadata.dividendPayAmount = root["META"]["fundamental"]["dividendPayAmount"].asDouble();
	metadata.dividendPayDate = root["META"]["fundamental"]["dividendPayDate"].asString();
	metadata.beta = root["META"]["fundamental"]["beta"].asDouble();
	metadata.vol1DayAvg = root["META"]["fundamental"]["vol1DayAvg"].asDouble();
	metadata.vol10DayAvg = root["META"]["fundamental"]["vol10DayAvg"].asDouble();
	metadata.vol3MonthAvg = root["META"]["fundamental"]["vol3MonthAvg"].asDouble();
	
}