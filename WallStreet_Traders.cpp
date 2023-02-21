#include "WallStreet_Traders.h"
#include "load_keys.h"
#include "sql_data_logger.h"


void intro();

int main(int, char **)
{
    time_keeper timer(1);
    intro();
    auto database_future = std::async(std::launch::async, []
                                      {
        load_sql_database database;
    return 0; });
    database_future.wait();



    ///////////////////////////////////////////////////////////////////////////////
    //functionality Test
	td_ameritrade_api api;
    std::string response1 = api.test_http_request_get_price_history(1);
    std::string response2 = api.test_http_request_get_search_instruments(1);
	sql_data_logger logger;
    logger.fundamentalsHandler("META", response2);
	logger.priceHistoryHandler("Minute", response1);
    ///////////////////////////////////////////////////////////////////////////////
    //functionality Test

    return 0;
}

void intro()
{
    std::string art[12] = {
        "                                              ",
        "           /$$           /$$                ",
        "          | $$          | $$                ",
        "  /$$$$$$ | $$  /$$$$$$ | $$$$$$$   /$$$$$$ ",
        " |____  $$| $$ /$$__  $$| $$__  $$ |____  $$",
        "  /$$$$$$$| $$| $$  \\ $$| $$  \\ $$  /$$$$$$$",
        " /$$__  $$| $$| $$  | $$| $$  | $$ /$$__  $$",
        "|  $$$$$$$| $$| $$$$$$$/| $$  | $$|  $$$$$$$",
        " \\_______/|__/| $$____/ |__/  |__/ \\_______/",
        "                                              ",
        "     Hello! Welcome to WallStreet Traders     ",
        "                                              "};

    for (int i = 0; i < sizeof(art) / sizeof(art[0]); i++)
    {
        std::cout << std::setw(80) << std::left << art[i] << std::endl;
    }
}