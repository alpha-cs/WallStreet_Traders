#pragma once

#include <iostream>
#include <string>
#include <fstream>

enum key_loader
{
	td_ameritrade_apikey = 0,
	sql_key,
	sizeof_keyloader
}typedef key_loader;

class load_keys
{
public:
	load_keys();
	load_keys(uint8_t loader);
	~load_keys();
	std::string get_td_apikey();
	std::string get_sql_hostname();
	std::string get_sql_username();
	std::string get_sql_password();
private:
	void set_td_ameritrade_apikey();
	void set_sql_key();
	
	std::string td_apikey_str;
	std::string sql_hostname_str;
	std::string sql_username_str;
	std::string sql_password_str;
	
	const std::string key_directory = "D:/_Programs/WallStreet_Traders/keys";
	const std::string sql_key_filename = "/sql.key.txt";
	const std::string td_apikey_filename = "/td.apikey.txt";
};