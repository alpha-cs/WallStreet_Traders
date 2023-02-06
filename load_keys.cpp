#include "load_keys.h"

load_keys::load_keys()
{
	set_td_ameritrade_apikey();
	set_sql_key();
}

load_keys::load_keys(uint8_t loader)
{
    for (int i = 0; i < sizeof_keyloader; i++)
    {
        if ((loader & (1 << i)) != 0) 
        {
				switch (i)
				{
				case td_ameritrade_apikey:
					set_td_ameritrade_apikey();
					break;
				case sql_key:
					set_sql_key();
					break;
				default:
					break;
				}
        }
    }
}

load_keys::~load_keys()
{
}

std::string load_keys::get_td_apikey()
{
    return td_apikey_str;
}

std::string load_keys::get_sql_hostname()
{
	return sql_hostname_str;
}

std::string load_keys::get_sql_username()
{
	return sql_username_str;
}

std::string load_keys::get_sql_password()
{
	return sql_password_str;
}

void load_keys::set_td_ameritrade_apikey()
{
    std::string filename = key_directory + td_apikey_filename;
    std::string full_api_key;
    try
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            std::getline(file, full_api_key);
            file.close();
            td_apikey_str = full_api_key.substr(full_api_key.find(":") + 1);
            if (td_apikey_str.empty())
            {
                std::cerr << "API key is empty. Terminating program." << std::endl;
                exit(1);
            }			
        }
        else
        {
            throw std::runtime_error("Error opening file: " + filename);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void load_keys::set_sql_key()
{
    std::string filename = key_directory + sql_key_filename;
    std::string line;
    try
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            while (std::getline(file, line))
            {
                if (line.find("hostname:") != std::string::npos)
                {
                    sql_hostname_str = line.substr(line.find(":") + 1);
                }
                else if (line.find("username:") != std::string::npos)
                {
                    sql_username_str = line.substr(line.find(":") + 1);
                }
                else if (line.find("password:") != std::string::npos)
                {
                    sql_password_str = line.substr(line.find(":") + 1);
                }
            }
            file.close();
            if (sql_hostname_str.empty() || sql_username_str.empty() || sql_password_str.empty())
            {
                std::cerr << "MySQL credentials are missing. Terminating program." << std::endl;
                exit(1);
            }
        }
        else
        {
            throw std::runtime_error("Error opening file: " + filename);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
