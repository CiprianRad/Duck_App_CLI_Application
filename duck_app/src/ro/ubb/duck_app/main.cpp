#include <iostream>
#include <memory>
#include "domain/Validators.h"
#include "repository/FileRepository.h"
#include "service/DuckService.h"
#include "service/LaneService.h"
#include "service/ReportsService.h"
#include "ui/Console.h"

int main() {
    auto duck_validator = std::make_shared<ro::ubb::duck_app::domain::DuckValidator>();
    auto duck_repository = std::make_shared<ro::ubb::duck_app::repository::FileRepository>(duck_validator, "ducks.txt");
    auto duck_service = std::make_shared<ro::ubb::duck_app::service::DuckService>(duck_repository);

    auto lane_validator = std::make_shared<ro::ubb::duck_app::domain::LaneValidator>();
    auto lane_repository = std::make_shared<ro::ubb::duck_app::repository::FileRepository>(lane_validator, "ducks.txt");
    auto lane_service = std::make_shared<ro::ubb::duck_app::service::LaneService>(lane_repository);

    auto reports_service = std::make_shared<ro::ubb::duck_app::service::ReportsService>(duck_repository, lane_repository);

    auto ui = std::make_shared<ro::ubb::duck_app::ui::UI>(duck_service, lane_service, reports_service);
    ui->runMenu();
}
