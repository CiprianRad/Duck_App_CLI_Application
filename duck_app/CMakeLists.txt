cmake_minimum_required(VERSION 3.20)
project(problema_natalie_cpp)

set(CMAKE_CXX_STANDARD 17)

# This variable points to the heart of your source code
set(APP_PATH src/ro/ubb/duck_app)

add_executable(problema_natalie_cpp
        main.cpp
        # Domain
        ${APP_PATH}/domain/Duck.cpp
        ${APP_PATH}/domain/Lane.cpp
        ${APP_PATH}/domain/Validators.cpp

        # Repository
        ${APP_PATH}/repository/Repository.cpp
        ${APP_PATH}/repository/FileRepository.cpp

        # Service
        ${APP_PATH}/service/DuckService.cpp
        ${APP_PATH}/service/LaneService.cpp
        ${APP_PATH}/service/ReportsService.cpp

        # UI
        ${APP_PATH}/ui/Console.cpp
)

# Tell CMake where to find the .h files so #include statements work
include_directories(src)