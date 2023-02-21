#include "td_ameritrade_api.h"

/**
 * @brief default constructor for td_ameritrade_api
 */
td_ameritrade_api::td_ameritrade_api()
{
	load_keys keys;
	api_key = keys.get_td_apikey();
}

/**
 * @brief destructor for td_ameritrade_api
 */
td_ameritrade_api::~td_ameritrade_api()
{
	
}

/**
 * @brief Get price history of a given symbol using TD Ameritrade API
 *
 */
std::string td_ameritrade_api::get_price_history(const std::string &symbol, const std::string &apikey, const std::string &startDate, const std::string &endDate)
{
    CURL *curl;
    CURLcode res;

    std::string url;
    if (startDate.empty())
    {
        url = build_url_get_price_history(symbol, apikey, endDate);
    }
    else
    {
        url = build_url_get_price_history(symbol, apikey, startDate, endDate);
    }

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else if (response.find("Bad request") != std::string::npos)
        {
            std::cerr << "Error: Bad request: " << symbol << " End Date: " << endDate << std::endl;
        }

        curl_easy_cleanup(curl);
        return response;
    }
}

std::string td_ameritrade_api::get_search_instruments(std::string symbol, std::string apikey)
{
    CURL *curl;
    CURLcode res;

    std::string url = "https://api.tdameritrade.com/v1/instruments?apikey=" + apikey + "&symbol=" + symbol + "&projection=fundamental";

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
        return response;
    }
}

size_t td_ameritrade_api::write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    std::string *response = reinterpret_cast<std::string *>(userdata);
    response->append(reinterpret_cast<char *>(ptr), size * nmemb);
    return size * nmemb;
}

/**
 * @brief Build URL for getting price history of a symbol from TD Ameritrade API
 *
 * @return URL for getting price history
 */
std::string td_ameritrade_api::build_url_get_price_history(std::string symbol, std::string apikey, std::string endDate)
{
    return base_url + symbol + "/pricehistory?apikey=" + apikey + "&periodType=day&period=1&frequencyType=minute&frequency=1&endDate=" + endDate + "&needExtendedHoursData=false";
}

/**
 * @brief Build URL for getting price history of a symbol from TD Ameritrade API
 *
 * @return URL for getting price history
 */
std::string td_ameritrade_api::build_url_get_price_history(std::string symbol, std::string apikey, std::string startDate, std::string endDate)
{
    return base_url + symbol + "/pricehistory?apikey=" + apikey + "&periodType=day&frequencyType=minute&frequency=1&endDate=" + endDate + "&startDate=" + startDate + "&needExtendedHoursData=true";
}

//testing
std::string td_ameritrade_api::test_http_request_get_price_history(bool show)
{
    td_ameritrade_api api_http_request_test;
    time_keeper unix_time(0);

    DateTime* start_datetime = new DateTime[1];
    DateTime* end_datetime = new DateTime[1];

    start_datetime[0].year = 2023;
    start_datetime[0].month = 1;
    start_datetime[0].day = 23;
    start_datetime[0].hour = 10;
    start_datetime[0].minute = 1;
    start_datetime[0].second = 0;

    end_datetime[0].year = 2023;
    end_datetime[0].month = 1;
    end_datetime[0].day = 23;
    end_datetime[0].hour = 10;
    end_datetime[0].minute = 5;
    end_datetime[0].second = 0;


    /*
    end_datetime[1].year = 2023;
    end_datetime[1].month = 1;
    end_datetime[1].day = 18;
    start_datetime[1].year = 2023;
    start_datetime[1].month = 1;
    start_datetime[1].day = 17;

    end_datetime[2].year = 2023;
    end_datetime[2].month = 1;
    end_datetime[2].day = 10;
    start_datetime[2].year = 2023;
    start_datetime[2].month = 1;
    start_datetime[2].day = 9;
	*/

    std::string price_history;
    for (int i = 0; i < 1; i++)
    {
        std::string end_unix = unix_time.date_to_unix_time_pst(end_datetime[i]);
        std::string start_unix = unix_time.date_to_unix_time_pst(start_datetime[i]);

        price_history = api_http_request_test.get_price_history("META", api_key, start_unix, end_unix);
        if (show)
        {
            std::cout << price_history << std::endl;
        }
    }

    delete[] end_datetime;
    delete[] start_datetime;
	return price_history;
}

std::string td_ameritrade_api::test_http_request_get_search_instruments(bool show)
{
    td_ameritrade_api api_http_request_test;
    std::string instruments = api_http_request_test.get_search_instruments("META", api_key);
    if (show)
    {
        std::cout << instruments << std::endl;
    }

	return instruments;
}