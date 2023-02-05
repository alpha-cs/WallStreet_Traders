#pragma once

#include <iostream>
#include <ctime>
#include <string>

/**
 * @brief Structure representing date and time.
 * yyyy MM DD HH mm ss
 */
typedef struct DateTime
{
    int year, month, day, hour = 0, minute = 0, second = 0;
} DateTime;

/**
 * @class time_keeper
 *
 * @brief Class to track and display time elapsed.
 *
 * The time_keeper class is used to track the time elapsed between when it's created and when it's destroyed.
 * It can also display the start and end time and duration if the "show_time" parameter is set to true
 * during object creation. Additionally, the class provides methods to convert date and time to UNIX time and
 * vice versa.
 */
class time_keeper
{
public:
    time_keeper(bool);
    ~time_keeper();

    std::string date_to_unix_time(const DateTime &date);
    std::string date_to_unix_time_pst(const DateTime &date);
    std::string unix_time_to_date(const std::string &unix_time);

private:
    time_t start;
    bool show_time;
};
