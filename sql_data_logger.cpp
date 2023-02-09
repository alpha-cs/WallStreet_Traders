#include "sql_data_logger.h"

sql_data_logger::sql_data_logger()
{
	try
	{
		sql_driver = get_driver_instance();
		sql_connection = sql_driver->connect(mysql_Host, mysql_User, mysql_Password);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		exit(1);
	}
}

sql_data_logger::~sql_data_logger()
{
	delete sql_result;
	delete sql_connection;
	delete sql_statement;
}

void sql_data_logger::fundamentalsHandler(const std::string metadata_symbol, const std::string &response)
{
	// Parse JSON response
	Json::Value root;
	Json::Reader reader;
	if (!reader.parse(response, root))
	{
		std::cerr << "Failed to parse response: " << reader.getFormattedErrorMessages() << std::endl;
		return;
	}

	// Extract values from JSON response
	metadata.cusip = root[metadata_symbol]["cusip"].asString();
	metadata.symbol = root[metadata_symbol]["symbol"].asString();
	metadata.description = root[metadata_symbol]["description"].asString();
	metadata.exchange = root[metadata_symbol]["exchange"].asString();
	metadata.assetType = root[metadata_symbol]["assetType"].asString();
	metadata.high52 = root[metadata_symbol]["fundamental"]["high52"].asDouble();
	metadata.low52 = root[metadata_symbol]["fundamental"]["low52"].asDouble();
	metadata.dividendAmount = root[metadata_symbol]["fundamental"]["dividendAmount"].asDouble();
	metadata.dividendYield = root[metadata_symbol]["fundamental"]["dividendYield"].asDouble();
	metadata.dividendDate = root[metadata_symbol]["fundamental"]["dividendDate"].asString();
	metadata.peRatio = root[metadata_symbol]["fundamental"]["peRatio"].asDouble();
	metadata.pegRatio = root[metadata_symbol]["fundamental"]["pegRatio"].asDouble();
	metadata.pbRatio = root[metadata_symbol]["fundamental"]["pbRatio"].asDouble();
	metadata.prRatio = root[metadata_symbol]["fundamental"]["prRatio"].asDouble();
	metadata.pcfRatio = root[metadata_symbol]["fundamental"]["pcfRatio"].asDouble();
	metadata.grossMarginTTM = root[metadata_symbol]["fundamental"]["grossMarginTTM"].asDouble();
	metadata.grossMarginMRQ = root[metadata_symbol]["fundamental"]["grossMarginMRQ"].asDouble();
	metadata.netProfitMarginTTM = root[metadata_symbol]["fundamental"]["netProfitMarginTTM"].asDouble();
	metadata.netProfitMarginMRQ = root[metadata_symbol]["fundamental"]["netProfitMarginMRQ"].asDouble();
	metadata.operatingMarginTTM = root[metadata_symbol]["fundamental"]["operatingMarginTTM"].asDouble();
	metadata.operatingMarginMRQ = root[metadata_symbol]["fundamental"]["operatingMarginMRQ"].asDouble();
	metadata.returnOnEquity = root[metadata_symbol]["fundamental"]["returnOnEquity"].asDouble();
	metadata.returnOnAssets = root[metadata_symbol]["fundamental"]["returnOnAssets"].asDouble();
	metadata.returnOnInvestment = root[metadata_symbol]["fundamental"]["returnOnInvestment"].asDouble();
	metadata.quickRatio = root[metadata_symbol]["fundamental"]["quickRatio"].asDouble();
	metadata.currentRatio = root[metadata_symbol]["fundamental"]["currentRatio"].asDouble();
	metadata.interestCoverage = root[metadata_symbol]["fundamental"]["interestCoverage"].asDouble();
	metadata.totalDebtToCapital = root[metadata_symbol]["fundamental"]["totalDebtToCapital"].asDouble();
	metadata.ltDebtToEquity = root[metadata_symbol]["fundamental"]["ltDebtToEquity"].asDouble();
	metadata.totalDebtToEquity = root[metadata_symbol]["fundamental"]["totalDebtToEquity"].asDouble();
	metadata.epsTTM = root[metadata_symbol]["fundamental"]["epsTTM"].asDouble();
	metadata.epsChangePercentTTM = root[metadata_symbol]["fundamental"]["epsChangePercentTTM"].asDouble();
	metadata.epsChangeYear = root[metadata_symbol]["fundamental"]["epsChangeYear"].asDouble();
	metadata.epsChange = root[metadata_symbol]["fundamental"]["epsChange"].asDouble();
	metadata.revChangeYear = root[metadata_symbol]["fundamental"]["revChangeYear"].asDouble();
	metadata.revChangeTTM = root[metadata_symbol]["fundamental"]["revChangeTTM"].asDouble();
	metadata.revChangeIn = root[metadata_symbol]["fundamental"]["revChangeIn"].asDouble();
	metadata.sharesOutstanding = root[metadata_symbol]["fundamental"]["sharesOutstanding"].asDouble();
	metadata.marketCapFloat = root[metadata_symbol]["fundamental"]["marketCapFloat"].asDouble();
	metadata.marketCap = root[metadata_symbol]["fundamental"]["marketCap"].asDouble();
	metadata.bookValuePerShare = root[metadata_symbol]["fundamental"]["bookValuePerShare"].asDouble();
	metadata.shortIntToFloat = root[metadata_symbol]["fundamental"]["shortIntToFloat"].asDouble();
	metadata.shortIntDayToCover = root[metadata_symbol]["fundamental"]["shortIntDayToCover"].asDouble();
	metadata.divGrowthRate3Year = root[metadata_symbol]["fundamental"]["divGrowthRate3Year"].asDouble();
	metadata.dividendPayAmount = root[metadata_symbol]["fundamental"]["dividendPayAmount"].asDouble();
	metadata.dividendPayDate = root[metadata_symbol]["fundamental"]["dividendPayDate"].asString();
	metadata.beta = root[metadata_symbol]["fundamental"]["beta"].asDouble();
	metadata.vol1DayAvg = root[metadata_symbol]["fundamental"]["vol1DayAvg"].asDouble();
	metadata.vol10DayAvg = root[metadata_symbol]["fundamental"]["vol10DayAvg"].asDouble();
	metadata.vol3MonthAvg = root[metadata_symbol]["fundamental"]["vol3MonthAvg"].asDouble();

	fundamentalsLogger(metadata);
	
}

void sql_data_logger::fundamentalsLogger(Fundamental &metadata)
{
	std::cout << "metadata = " << metadata.cusip << std::endl;
	try
	{
		sql_statement = sql_connection->prepareStatement(fundamentalQuery);
		sql_statement->setString(1, metadata.cusip);
		sql_statement->setString(2, metadata.symbol);
		sql_statement->setString(3, metadata.description);
		sql_statement->setString(4, metadata.exchange);
		sql_statement->setString(5, metadata.assetType);
		sql_statement->setDouble(6, metadata.high52);
		sql_statement->setDouble(7, metadata.low52);
		sql_statement->setDouble(8, metadata.dividendAmount);
		sql_statement->setDouble(9, metadata.dividendYield);
		sql_statement->setString(10, metadata.dividendDate);
		sql_statement->setDouble(11, metadata.peRatio);
		sql_statement->setDouble(12, metadata.pegRatio);
		sql_statement->setDouble(13, metadata.pbRatio);
		sql_statement->setDouble(14, metadata.prRatio);
		sql_statement->setDouble(15, metadata.pcfRatio);
		sql_statement->setDouble(16, metadata.grossMarginTTM);
		sql_statement->setDouble(17, metadata.grossMarginMRQ);
		sql_statement->setDouble(18, metadata.netProfitMarginTTM);
		sql_statement->setDouble(19, metadata.netProfitMarginMRQ);
		sql_statement->setDouble(20, metadata.operatingMarginTTM);
		sql_statement->setDouble(21, metadata.operatingMarginMRQ);
		sql_statement->setDouble(22, metadata.returnOnEquity);
		sql_statement->setDouble(23, metadata.returnOnAssets);
		sql_statement->setDouble(24, metadata.returnOnInvestment);
		sql_statement->setDouble(25, metadata.quickRatio);
		sql_statement->setDouble(26, metadata.currentRatio);
		sql_statement->setDouble(27, metadata.interestCoverage);
		sql_statement->setDouble(28, metadata.totalDebtToCapital);
		sql_statement->setDouble(29, metadata.ltDebtToEquity);
		sql_statement->setDouble(30, metadata.totalDebtToEquity);
		sql_statement->setDouble(31, metadata.epsTTM);
		sql_statement->setDouble(32, metadata.epsChangePercentTTM);
		sql_statement->setDouble(33, metadata.epsChangeYear);
		sql_statement->setDouble(34, metadata.epsChange);
		sql_statement->setDouble(35, metadata.revChangeYear);
		sql_statement->setDouble(36, metadata.revChangeTTM);
		sql_statement->setDouble(37, metadata.revChangeIn);
		sql_statement->setDouble(38, metadata.sharesOutstanding);
		sql_statement->setDouble(39, metadata.marketCapFloat);
		sql_statement->setDouble(40, metadata.marketCap);
		sql_statement->setDouble(41, metadata.bookValuePerShare);
		sql_statement->setDouble(42, metadata.shortIntToFloat);
		sql_statement->setDouble(43, metadata.shortIntDayToCover);
		sql_statement->setDouble(44, metadata.divGrowthRate3Year);
		sql_statement->setDouble(45, metadata.dividendPayAmount);
		sql_statement->setString(46, metadata.dividendPayDate);
		sql_statement->setDouble(47, metadata.beta);
		sql_statement->setDouble(48, metadata.vol1DayAvg);
		sql_statement->setDouble(49, metadata.vol10DayAvg);
		sql_statement->setDouble(50, metadata.vol3MonthAvg);
		sql_statement->execute();
		sql_result = sql_statement->getResultSet();
	}
	catch (sql::SQLException& e)
	{
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
	std::cout << std::endl;
}