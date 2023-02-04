#include "WallStreet_Traders.h"
#include "load_sql_database.h"
#include "time_keeper.h"
#include "td_ameritrade_api.h"

std::string api_key;

void intro();
void get_td_apikey();

int main(int, char**)
{
    td_ameritrade_api api;
	
	
    get_td_apikey();

    time_keeper timer;
    intro();
	
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