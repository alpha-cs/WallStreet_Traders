#pragma once

#include <iostream>
#include <string>
#include <curl/curl.h>

class td_ameritrade_api
{
public:
	td_ameritrade_api();
	~td_ameritrade_api();
	void get_price_history(const std::string& symbol, const std::string& apikey, const std::string& startDate = "", const std::string& endDate = "");

	std::string build_url_get_price_history(std::string symbol, std::string apikey, std::string startDate, std::string endDate);
	std::string build_url_get_price_history(std::string symbol, std::string apikey, std::string endDate);

private:
	const std::string base_url = "https://api.tdameritrade.com/v1/marketdata/";
};