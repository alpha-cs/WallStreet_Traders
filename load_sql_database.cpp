#include "load_sql_database.h"

load_sql_database::load_sql_database()
{
	try
	{
		sql_driver = get_driver_instance();
		sql_connection = sql_driver->connect(mysql_Host, mysql_User, mysql_Password);
		sql_table_status = check_sql_tables();
		dbStatus required_table_status = get_required_table_status();
		
		if (sql_table_status != required_table_status)
		{
			std::cout << "Missing tables. Creating tables..." << std::endl;
			make_sql_table();
		}
		std::cout << "SQL Table Status: " << std::bitset<8>(sql_table_status) << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		exit(1);
	}
}

load_sql_database::~load_sql_database()
{
	delete sql_result;
	delete sql_statement;
	delete sql_connection;
}

void load_sql_database::make_sql_table()
{
	std::string sql_table[] = { makeTable_company_fundamental, makeTable_td_price_history_minute, makeTable_td_price_history_daily, makeTable_td_price_history_weekly, makeTable_td_price_history_monthly};
	for (int i = 0; i < sizeof_sql_tdameritrade_table; i++)
	{
		if ((sql_table_status & (1 << i)) == 0)
		{
			try
			{
				std::string query = sql_table[i];
				sql_statement = sql_connection->prepareStatement(query);
				sql_statement->execute();
				std::cout << "Table bit index " << i << " created." << std::endl;
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
				exit(1);
			}
		}
	}
	sql_table_status = check_sql_tables();
}

dbStatus load_sql_database::check_table(const std::string &table_name)
{
	try
	{
		// Create the query string to check if the table already exists.
		std::string checkQuery = "SHOW TABLES FROM " + (std::string)sql_database + " LIKE '" + table_name + "'";
		sql_statement = sql_connection->prepareStatement(checkQuery);
		sql_result = sql_statement->executeQuery();
		if (sql_result->next())
		{
			if (table_name == "company_fundamental")
			{
				return 1 << company_fundamental;
			}
			else if (table_name == "td_price_history_minute")
			{
				return 1 << td_price_history_minute;
			}
			else if (table_name == "td_price_history_daily")
			{
				return 1 << td_price_history_daily;
			}
			else if (table_name == "td_price_history_weekly")
			{
				return 1 << td_price_history_weekly;
			}
			else if (table_name == "td_price_history_monthly")
			{
				return 1 << td_price_history_monthly;
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		exit(1);
	}
	return 0;
}

dbStatus load_sql_database::get_required_table_status()
{
	dbStatus required_table_status = 0;
	for (int i = 0; i < sizeof_sql_tdameritrade_table; i++)
	{
		required_table_status |= (1 << i);
	}
	return required_table_status;
}

dbStatus load_sql_database::check_company_fundamental()
{
	return check_table(("company_fundamental"));
}
dbStatus load_sql_database::check_td_price_history_minute()
{
	return check_table("td_price_history_minute");
}
dbStatus load_sql_database::check_td_price_history_daily()
{
	return check_table("td_price_history_daily");
}
dbStatus load_sql_database::check_td_price_history_weekly()
{
	return check_table("td_price_history_weekly");
}
dbStatus load_sql_database::check_td_price_history_monthly()
{
	return check_table("td_price_history_monthly");
}

dbStatus load_sql_database::check_sql_tables()
{
	dbStatus status = 0;
	status |= check_company_fundamental();
	status |= check_td_price_history_minute();
	status |= check_td_price_history_daily();
	status |= check_td_price_history_weekly();
	status |= check_td_price_history_monthly();
	return status;
}