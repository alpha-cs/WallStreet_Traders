#include "WallStreet_Traders.h"
#include "load_sql_database.h"
#include "time_keeper.h"
#include "td_ameritrade_api.h"

std::string api_key;

void intro();
void get_td_apikey();
void test_http_request_get_price_history(bool);
void test_http_request_get_search_instruments(bool);


int main(int, char**)
{	
    get_td_apikey();
    time_keeper timer(1);	
    intro();

    test_http_request_get_price_history(0);
    test_http_request_get_search_instruments(0);
	
    auto database_future = std::async(std::launch::async, [] {
        load_sql_database database;
    return 0;
        });

    database_future.wait();

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

void get_td_apikey() {
    std::string directory = "D:/_Programs/WallStreet_Traders/td_dev.api"; // path to the directory
    std::string filename = directory + "/key.txt"; // filename
    std::string full_api_key;

    try {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::getline(file, full_api_key);
            file.close();
            api_key = full_api_key.substr(full_api_key.find(":") + 1);
            if (api_key.empty()) {
                std::cerr << "API key is empty. Terminating program." << std::endl;
                exit(1);
            }
        }
        else {
            throw std::runtime_error("Error opening file: " + filename);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void test_http_request_get_price_history(bool show) {
    td_ameritrade_api api_http_request_test;
    time_keeper unix_time(0);

    DateTime* end_datetime = new DateTime[3];
    DateTime* start_datetime = new DateTime[3];


    end_datetime[0].year = 2023;
    end_datetime[0].month = 1;
    end_datetime[0].day = 24;
    end_datetime[0].hour = 0;
    end_datetime[0].minute = 0;
    end_datetime[0].second = 0;
    start_datetime[0].year = 2023;
    start_datetime[0].month = 1;
    start_datetime[0].day = 23;
    start_datetime[0].hour = 0;
    start_datetime[0].minute = 0;
    start_datetime[0].second = 0;

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

    for (int i = 0; i < 3; i++) {
        std::string end_unix = unix_time.date_to_unix_time_pst(end_datetime[i]);
        std::string start_unix = unix_time.date_to_unix_time_pst(start_datetime[i]);

        std::string price_history = api_http_request_test.get_price_history("META", api_key, start_unix, end_unix);
		if (show) {
			std::cout << price_history << std::endl;
		}
    }

    delete[] end_datetime;
    delete[] start_datetime;
}

void test_http_request_get_search_instruments(bool show) {
	td_ameritrade_api api_http_request_test;
	std::string instruments = api_http_request_test.get_search_instruments("META", api_key);
    if (show) {
        std::cout << instruments << std::endl;
    }
}