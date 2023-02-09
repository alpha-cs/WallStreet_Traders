#pragma once

#include <iostream>
#include <string>
#include <curl/curl.h>
#include "time_keeper.h"
#include "load_keys.h"

class td_ameritrade_api
{
public:
	td_ameritrade_api();
	~td_ameritrade_api();
	std::string get_price_history(const std::string &symbol, const std::string &apikey, const std::string &startDate = "", const std::string &endDate = "");
	std::string get_search_instruments(std::string symbol, std::string apikey);
	static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata);
	std::string build_url_get_price_history(std::string symbol, std::string apikey, std::string startDate, std::string endDate);
	std::string build_url_get_price_history(std::string symbol, std::string apikey, std::string endDate);

	//testing
	void test_http_request_get_price_history(bool);
	std::string test_http_request_get_search_instruments(bool);
	
private:
	const std::string base_url = "https://api.tdameritrade.com/v1/marketdata/";
	std::string api_key;
};