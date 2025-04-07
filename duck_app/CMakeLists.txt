cmake_minimum_required(VERSION 3.30)
project(duck_app)

set(CMAKE_CXX_STANDARD 20)

add_executable(duck_app src/ro/ubb/duck_app/main.cpp
        src/ro/ubb/duck_app/domain/Duck.h
        src/ro/ubb/duck_app/domain/Lane.h
        src/ro/ubb/duck_app/domain/validators.h
        src/ro/ubb/duck_app/repository/Repository.h
        src/ro/ubb/duck_app/repository/FileRepository.h
        src/ro/ubb/duck_app/service/DuckService.h
        src/ro/ubb/duck_app/service/LaneService.h
        src/ro/ubb/duck_app/service/ReportsService.h
        src/ro/ubb/duck_app/ui/Console.h
)
