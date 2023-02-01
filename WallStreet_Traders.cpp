#define API_KEY get_td_apikey()

#include "WallStreet_Traders.h"
#include "load_sql_database.h"
#include "time_keeper.h"

std::string api_key;

void intro();
void get_td_apikey();

int main(int, char**)
{
    API_KEY;

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
    std::string directory = "D:/_Programs/WallStreet_Traders/td_dev.api"; // specify the path to the directory
    std::string filename = directory + "/key.txt"; // specify the filename
    std::string full_api_key;

    try {
        // Open the file
        std::ifstream file(filename);
        if (file.is_open()) {
            // Read the full API key from the file
            std::getline(file, full_api_key);
            file.close();

            // Extract the API key that you need
            api_key = full_api_key.substr(full_api_key.find(":") + 1);

            // Use the API key to access TD Ameritrade API
            // ...

            std::cout << "API key successfully read: " << api_key << std::endl;
        }
        else {
            throw std::runtime_error("Error opening file: " + filename);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}