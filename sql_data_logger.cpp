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

void sql_data_logger::reset_auto_increment(std::string table)
{
	try
	{
		std::string query = "ALTER TABLE " + table + " AUTO_INCREMENT = 1";
		sql_statement = sql_connection->prepareStatement(query);
		sql_statement->execute();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		exit(1);
	}
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

/*
{
  "candles": [
	{
	  "open": 139.33,
	  "high": 141.5,
	  "low": 138.66,
	  "close": 140.7974,
	  "volume": 3266682,
	  "datetime": 1674484200000
	},
	{
	  "open": 140.84,
	  "high": 141.99,
	  "low": 140.665,
	  "close": 141.9322,
	  "volume": 1931593,
	  "datetime": 1674486000000
	},
	{
	  "open": 141.94,
	  "high": 142.28,
	  "low": 141.545,
	  "close": 142.09,
	  "volume": 1245903,
	  "datetime": 1674487800000
	},
	{
	  "open": 142.1,
	  "high": 143.27,
	  "low": 141.99,
	  "close": 142.645,
	  "volume": 1471935,
	  "datetime": 1674489600000
	},
	{
	  "open": 142.68,
	  "high": 142.81,
	  "low": 142.41,
	  "close": 142.73,
	  "volume": 1023768,
	  "datetime": 1674491400000
	},
	{
	  "open": 142.73,
	  "high": 143.09,
	  "low": 142.35,
	  "close": 142.63,
	  "volume": 1187357,
	  "datetime": 1674493200000
	},
	{
	  "open": 142.63,
	  "high": 142.92,
	  "low": 142.3,
	  "close": 142.745,
	  "volume": 1095486,
	  "datetime": 1674495000000
	},
	{
	  "open": 142.74,
	  "high": 143.04,
	  "low": 142.65,
	  "close": 142.91,
	  "volume": 837430,
	  "datetime": 1674496800000
	},
	{
	  "open": 142.92,
	  "high": 143.16,
	  "low": 142.3,
	  "close": 142.445,
	  "volume": 828275,
	  "datetime": 1674498600000
	},
	{
	  "open": 142.44,
	  "high": 142.8819,
	  "low": 142.2,
	  "close": 142.675,
	  "volume": 947825,
	  "datetime": 1674500400000
	},
	{
	  "open": 142.69,
	  "high": 142.91,
	  "low": 142.09,
	  "close": 142.75,
	  "volume": 1167767,
	  "datetime": 1674502200000
	},
	{
	  "open": 142.75,
	  "high": 143.37,
	  "low": 142.41,
	  "close": 142.985,
	  "volume": 1374991,
	  "datetime": 1674504000000
	},
	{
	  "open": 142.99,
	  "high": 143.76,
	  "low": 142.86,
	  "close": 143.27,
	  "volume": 2475754,
	  "datetime": 1674505800000
	}
  ],
  "symbol": "META",
  "empty": false
}
*/
void sql_data_logger::priceHistoryHandler(const std::string frequencyType, const std::string& response)
{
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(response, root);
	if (!parsingSuccessful)
	{
		// report to the user the failure and their locations in the document.
		std::cout << "Failed to parse configuration\n"
			<< reader.getFormattedErrorMessages();
		return;
	}
	
	Json::Value metadata_candles = root["candles"];
	priceHistory priceHistory;
	priceHistory.frequencyType = frequencyType;
	priceHistory.symbol = root["symbol"].asString();

	for (int i = 0; i < metadata_candles.size(); i++)
	{
		priceHistory.open = metadata_candles[i]["open"].asDouble();
		priceHistory.high = metadata_candles[i]["high"].asDouble();
		priceHistory.low = metadata_candles[i]["low"].asDouble();
		priceHistory.close = metadata_candles[i]["close"].asDouble();
		priceHistory.volume = metadata_candles[i]["volume"].asUInt64();
		priceHistory.datetime = metadata_candles[i]["datetime"].asUInt64();
		priceHistoryLogger(priceHistory);
	}
}





void sql_data_logger::fundamentalsLogger(Fundamental &metadata)
{
	reset_auto_increment("`tdameritrade`.`company_fundamental`");
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

void sql_data_logger::priceHistoryLogger(priceHistory& priceHistory)
{
	try
	{
		if (priceHistory.frequencyType == "Minute") {
			reset_auto_increment("`tdameritrade`.`td_price_history_minute`");
			sql_statement = sql_connection->prepareStatement(Minute_priceHistoryQuery);
		}
		else if (priceHistory.frequencyType == "Daily") {
			reset_auto_increment("`tdameritrade`.`td_price_history_daily`");
			sql_statement = sql_connection->prepareStatement(Daily_priceHistoryQuery);
		}
		else if (priceHistory.frequencyType == "Weekly") {
			reset_auto_increment("`tdameritrade`.`td_price_history_weekly`");
			sql_statement = sql_connection->prepareStatement(Weekly_priceHistoryQuery);
		}
		else if (priceHistory.frequencyType == "Monthly") {
			reset_auto_increment("`tdameritrade`.`td_price_history_weekly`");
			sql_statement = sql_connection->prepareStatement(Monthly_priceHistoryQuery);
		}
		else
		{
			std::cout << "Invalid frequency type" << std::endl; 
		}
		sql_statement->setString(1, priceHistory.symbol);
		sql_statement->setDouble(2, priceHistory.open);
		sql_statement->setDouble(3, priceHistory.high);
		sql_statement->setDouble(4, priceHistory.low);
		sql_statement->setDouble(5, priceHistory.close);
		sql_statement->setUInt64(6, (priceHistory.volume));
		sql_statement->setUInt64(7, (priceHistory.datetime));

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
}
