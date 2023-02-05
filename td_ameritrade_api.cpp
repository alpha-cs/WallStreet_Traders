#include "td_ameritrade_api.h"

/**
 * @brief default constructor for td_ameritrade_api
 */
td_ameritrade_api::td_ameritrade_api()
{
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
    return base_url + symbol + "/pricehistory?apikey=" + apikey + "&periodType=day&period=10&frequencyType=minute&frequency=1&endDate=" + endDate + "&needExtendedHoursData=true";
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
