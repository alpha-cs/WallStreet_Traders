# CMakeList.txt : CMake project for WallStreet_Traders, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project ("WallStreet_Traders")

# curl x64-release
include("D:/_Programs/github_builds/vcpkg/scripts/buildsystems/vcpkg.cmake")
find_package(CURL CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

# MySQL C++ Connector x64-release
set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR "D:\\_Programs\\WallStreet_Traders\\builds\\MySQL\\x64_Release")
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib64/vs14)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include/jdbc)

# Add source to this project's executable.
add_executable (WallStreet_Traders "WallStreet_Traders.cpp" "WallStreet_Traders.h" "time_keeper.cpp" "time_keeper.h" "sql_headers.h"  "load_sql_database.cpp" "load_sql_database.h" "td_ameritrade_api.cpp" "td_ameritrade_api.h" "sql_data_logger.h" "sql_data_logger.cpp" "load_keys.cpp" "load_keys.h")

target_link_libraries(WallStreet_Traders mysqlcppconn CURL::libcurl JsonCpp::JsonCpp)

target_compile_features(WallStreet_Traders PRIVATE cxx_range_for)  

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WallStreet_Traders PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
install (TARGETS WallStreet_Traders DESTINATION "C:\\Users\\Public\\WallStreet_Traders")