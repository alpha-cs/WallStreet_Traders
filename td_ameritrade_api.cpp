#include "td_ameritrade_api.h"

td_ameritrade_api::td_ameritrade_api()
{
}

td_ameritrade_api::~td_ameritrade_api()
{
}

void td_ameritrade_api::get_price_history(const std::string& symbol, const std::string& apikey, const std::string& startDate, const std::string& endDate)
{
	CURL* curl;
	CURLcode res;

	std::string url;
	if (startDate.empty()) {
		url = build_url_get_price_history(symbol, apikey, endDate);
	}
	else {
		url = build_url_get_price_history(symbol, apikey, startDate, endDate);
	}

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		}
		curl_easy_cleanup(curl);
	}
}

std::string td_ameritrade_api::build_url_get_price_history(std::string symbol, std::string apikey, std::string endDate)
{
	return base_url + symbol + "/pricehistory?apikey=" + apikey + "&periodType=day&period=10&frequencyType=minute&frequency=1&endDate=" + endDate + "&needExtendedHoursData=true";
}

std::string td_ameritrade_api::build_url_get_price_history(std::string symbol, std::string apikey, std::string startDate, std::string endDate)
{
	return base_url + symbol + "/pricehistory?apikey=" + apikey + "&periodType=day&frequencyType=minute&frequency=1&endDate=" + endDate + "&startDate=" + startDate + "&needExtendedHoursData=true";
}
