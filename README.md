<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/alpha-cs/WallStreet_Traders">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">WallStreet Traders</h3>

  <p align="center">
    A Stock Market Application for planning strategies and simulating strategies.
    <br />
    <a href="https://github.com/alpha-cs/WallStreet_Traders"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/alpha-cs/WallStreet_Traders">View Demo</a>
    ·
    <a href="https://github.com/alpha-cs/WallStreet_Traders/issues">Report Bug</a>
    ·
    <a href="https://github.com/alpha-cs/WallStreet_Traders/issues">Request Feature</a>
  </p>
</div>


<!-- ABOUT THE PROJECT -->
## About The Project

A Stock Market Application for planning strategies and simulating strategies. A multi-threaded windows desktop application with using realtime Stock Market data from the most popular trading exchanges. Giving traders a powerful fast tool for planning and executing trading strategies. 

Here's why:
* Get rid of all the flashing lights, advertisements, and distractions and get straight to point. Create alerts, automatic orders, and simulate a strategy to visualize a algorithms potential. 
* When I was daily trading I wanted a toolthat would generate hystorical data for any algorithm and any stock based on certain limits.
* Store local Stock Market data to continue planning even when offline.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With
* C/C++
* CMake
* CURL
* MySQL Connector C++
* TD Ameritrade Dev API
* MSVC

<!-- GETTING STARTED -->
## Getting Started
Before you run this application you will need to setup CMakeList.txt and create a TD Ameritrade account.
Ensure that your user enviornment variable Path targets the location for "mysqlcppconn-9-vs14.dll" and "libcurl.dll".
### Prerequisites

#### TD Ameritrade
* Developer API Access
Go to https://developer.tdameritrade.com/apis and request access to the API.
Create an app to get your own APIKEY. Make sure to make this key never expire and use "http://localhost" as the URL CALLBACK unless you know what you are doing. Becuase I don't.

#### CURL
* libcurl build
You will need msvc command prompt to build curl static library.
1. Open MSVC x64 or x86 Cross Tool Command Prompt
2. Clone the vcpkg repository and build curl static library
```sh
  git clone https://github.com/Microsoft/vcpkg.git
  ```
```sh
  cd vcpkg
  ```
```sh
  bootstrap-vcpkg.sh
  ```
```sh
  vcpkg.exe integrate install
  ```  
* curl x64 Installation  
```sh
  vcpkg.exe install curl:x64-windows
  ``` 
* curl x86 Installation
```sh
  vcpkg.exe install curl:[tool]
  ``` 
3. Once build replace the CMakeLists.txt with your vcpkg path, for example: include("D:/_Programs/github_builds/vcpkg/scripts/buildsystems/vcpkg.cmake")
  
#### MySQL
**You must create database "tdameritrade" to store tables**
**If you have different Host, Username, and password you will need to update sql_server_connection.txt**
* MySQL Connector C++ 8.0
Windows x64 and x86 (32-bit) versions of MySQL come preinstalled in this project. If you wish to use a different version, you can download it from the MySQL website.
The MySQL Connector C++ x64 release version is already set in the CMakeLists.txt. To target the x86 release version, change the following in the CMakeLists.txt file:
```sh
  Change MySQL\\x64_Release to MySQL\\x32_Release
  ``` 
```sh
  Change lib64/vs14 to lib/vs14 
  ``` 

<!-- ROADMAP -->
## Roadmap

- [x] README.md
- [x] Build Database
- [ ] TD Ameritrade HTTP Request
    - [ ] Transition to Charles Schwab api once integration is complete
    - [ ] Get Price History
    - [ ] Get Search Instruments
- [ ] Logging Stock Market Data
    - [ ] Watchlist
    - [ ] On start up, fill the missing data gap
- [ ] Static Algorithms
    - [ ] 2
    - [ ] 5
    - [ ] 10
    - [ ] 25
- [ ] Dynamic Algorithms
    - [ ] 2
    - [ ] 5
    - [ ] 10
    - [ ] 25
- [ ] Logging Algorithm Request
    - [ ] On start up, fill the missing data gap
- [ ] Multi-Threading worker threads
- [ ] User Menu
- [ ] Create orders

See the [open issues](https://github.com/othneildrew/Best-README-Template/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!
