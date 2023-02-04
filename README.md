# WallStreet_Traders
A stock market application for planning strategies and simulating trading algorithms, allowing users to calculate hypothetical profits or losses based on historical data and mathematical indicators. The purpose of the stock market application is to provide traders with a powerful tool for planning and executing their trading strategies, using historical data and mathematical indicators to identify the best times to buy and sell. This project aims to help traders improve their performance and maximize their returns.

#builds
You will need to install vcpkg and install the following packages: curl

curl x32 guide:
Open MSVC x86 Cross Tool Command Prompt
cd <your path> i.e "D:/_Programs/github_builds/"
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.sh
vcpkg.exe integrate install
vcpkg.exe install curl:[tool]
Replace CMakeLists.txt with your vcpkg path i.e "include("D:/_Programs/github_builds/vcpkg/scripts/buildsystems/vcpkg.cmake")"

curl x64 guide:
Open MSVC x64 Cross Tool Command Prompt
cd <your path> i.e "D:/_Programs/github_builds/"
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.sh
vcpkg.exe integrate install
vcpkg.exe install curl:x64-windows
Replace CMakeLists.txt with your vcpkg path i.e "include("D:/_Programs/github_builds/vcpkg/scripts/buildsystems/vcpkg.cmake")"

MySQL guide:
Windows x64 and x86 (32-bit) come preinstalled in this project. If you want to use a different version, you can download it from here: https://dev.mysql.com/downloads/installer/.
MySQL Connector C++ x64 release version is already set in the CMakeLists.txt.
You will need to change the dir in the CMakeLists.txt file to target the x86 release version. 
from "MySQL\\x64_Release" to "MySQL\\x32_Release" And "lib64/vs14" to "lib/vs14"