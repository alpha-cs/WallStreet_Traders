#include "time_keeper.h"

time_keeper::time_keeper()
{
    start = time(nullptr); // get the current time at the start of the function
    std::cout << "Start Time: " << ctime(&start) << std::endl;
}

time_keeper::~time_keeper()
{
    time_t end = time(nullptr);             // get the current time at the end of the function
    double duration = difftime(end, start); // calculate the duration
    std::cout << "End Time: " << ctime(&end) << std::endl;
    std::cout << "Duration: " << duration << " seconds" << std::endl;
}
