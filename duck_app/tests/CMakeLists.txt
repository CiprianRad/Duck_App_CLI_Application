set(APP_PATH ../src/ro/ubb/duck_app)

add_executable(run_tests
        test_all.cpp
        ${APP_PATH}/domain/Duck.cpp
        ${APP_PATH}/domain/Lane.cpp
        ${APP_PATH}/domain/Validators.cpp
        ${APP_PATH}/repository/Repository.cpp
        ${APP_PATH}/repository/FileRepository.cpp
        ${APP_PATH}/service/DuckService.cpp
        ${APP_PATH}/service/LaneService.cpp
        ${APP_PATH}/service/ReportsService.cpp
        ${APP_PATH}/ui/Console.cpp
)

target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${APP_PATH})

target_compile_options(run_tests PRIVATE --coverage -fprofile-arcs -ftest-coverage)
target_link_options(run_tests PRIVATE --coverage)
