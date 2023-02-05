#include "time_keeper.h"

/**
 * Default constructor that initializes the start time to the current time and show_time to the value passed in.
 * @param show Whether or not to display time information
 * 1 = display
 * 0 = don't display
 */
time_keeper::time_keeper(bool show)
{
    show_time = show;
    if (show_time)
    {
        start = time(nullptr);
        std::cout << "Start Time: " << ctime(&start) << std::endl;
    }
}

/**
 * Destructor that displays the end time and duration if show_time is true.
 */
time_keeper::~time_keeper()
{
    if (show_time)
    {
        time_t end = time(nullptr);
        double duration = difftime(end, start);
        std::cout << "End Time: " << ctime(&end) << std::endl;
        std::cout << "Duration: " << duration << " seconds" << std::endl;
    }
}

/**
 * Converts a PST DateTime object to Unix time.
 * @param date The DateTime object to convert
 * @return The Unix time string
 */
std::string time_keeper::date_to_unix_time(const DateTime &date)
{
    std::tm date_time = {};
    date_time.tm_year = date.year - 1900;
    date_time.tm_mon = date.month - 1;
    date_time.tm_mday = date.day;
    date_time.tm_hour = date.hour;
    date_time.tm_min = date.minute;
    date_time.tm_sec = date.second;

    auto unix_time = std::mktime(&date_time);
    return std::to_string(unix_time * 1000);
}

std::string time_keeper::date_to_unix_time_pst(const DateTime &date)
{
    std::tm date_time = {};
    date_time.tm_year = date.year - 1900;
    date_time.tm_mon = date.month - 1;
    date_time.tm_mday = date.day;
    date_time.tm_hour = date.hour;
    date_time.tm_min = date.minute;
    date_time.tm_sec = date.second;

    // Determine the timezone offset for Pacific Standard Time (PST)
    std::string timezone_offset = "";
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::gmtime(&t);
    tm.tm_isdst = -1;
    std::mktime(&tm);
    int offset = (tm.tm_hour - date_time.tm_hour) * 3600 + (tm.tm_min - date_time.tm_min) * 60;
    if (offset < 0)
    {
        timezone_offset = "+";
        offset = -offset;
    }
    else
    {
        timezone_offset = "-";
    }
    int offset_hours = offset / 3600;
    int offset_minutes = (offset % 3600) / 60;
    timezone_offset += std::to_string(offset_hours);
    if (offset_minutes != 0)
    {
        timezone_offset += ":" + std::to_string(offset_minutes);
    }

    // Adjust the time based on the timezone offset
    date_time.tm_hour -= offset_hours;
    date_time.tm_min -= offset_minutes;
    std::mktime(&date_time);

    auto unix_time = std::mktime(&date_time);
    return std::to_string(unix_time * 1000);
}

/**
 * Converts a Unix time string to a date string.
 * @param unix_time The Unix time string to convert
 * @return The date string
 */
std::string time_keeper::unix_time_to_date(const std::string &unix_time)
{
    auto unix_time_num = std::stoll(unix_time) / 1000;
    std::tm *date_time = std::gmtime(&unix_time_num);
    char buffer[20];
    std::strftime(buffer, 20, "%Y %m %d %H %M %S", date_time);
    return buffer;
}