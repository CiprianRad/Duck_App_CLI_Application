#include <cstdio>
#include <vector>
#include "domain/Duck.h"
#include "domain/Lane.h"
#include "domain/validators.h"
#include "repository/Repository.h"
#include "repository/FileRepository.h"
#include "service/DuckService.h"
#include "service/LaneService.h"
#include "service/ReportsService.h"
#include "ui/Console.h"

int main() {
    // int duck_id = 1;
    // int speed = 4;
    // int resistance = 7;
    // printf("Hello World\n");
    // ro::ubb::duck_app::domain:: Duck duck = ro::ubb::duck_app::domain:: Duck(duck_id, speed, resistance);
    // std::cout << duck << std::endl;
    // ro::ubb::duck_app::domain:: Duck duck1;
    // std::cout << duck1 << std::endl;
    // int lane_id = 1;
    // int length = 7;
    // ro::ubb::duck_app::domain::Lane lane = ro::ubb::duck_app::domain::Lane(lane_id, length);
    // std::cout << lane << std::endl;
    // ro::ubb::duck_app::domain::Lane lane_1;
    // std::cout << lane_1 << std::endl;
    //
    //
    //
    //
    //
    // std::shared_ptr<ro::ubb::duck_app::domain::EntityValidator> duck_validator = std::make_shared<ro::ubb::duck_app::domain::DuckValidator>();
    // ro::ubb::duck_app::repository::Repository duck_repository(duck_validator);
    // std::shared_ptr<ro::ubb::duck_app::domain::EntityValidator> lane_validator = std::make_shared<ro::ubb::duck_app::domain::LaneValidator>();
    // ro::ubb::duck_app::repository::Repository lane_repository(lane_validator);
    // // std::shared_ptr<ro::ubb::duck_app::domain::Duck> duck2 = std::make_shared<ro::ubb::duck_app::domain::Duck>();
    // // std::static_pointer_cast<ro::ubb::duck_app::domain::Entity>(duck2);
    // // std::shared_ptr<ro::ubb::duck_app::domain::Lane> lane2 = std::make_shared<ro::ubb::duck_app::domain::Lane>();
    // // duck_repository.save(duck2);
    // std::shared_ptr<ro::ubb::duck_app::domain::Duck> duck2 = std::make_shared<ro::ubb::duck_app::domain::Duck>(1, 5, 10);
    //
    // duck_repository.save(std::static_pointer_cast<ro::ubb::duck_app::domain::Entity>(duck2));
    // // std::vector<std::shared_ptr<ro::ubb::duck_app::domain::Duck>> result = duck_repository.findAll();
    // auto all_entities = duck_repository.findAll();
    // for (const auto &entity : all_entities) {
    //     std::shared_ptr<ro::ubb::duck_app::domain::Duck> duck = std::dynamic_pointer_cast<ro::ubb::duck_app::domain::Duck>(entity);
    //     if (duck) {
    //         std::cout<<*duck<<std::endl;
    //     }
    // }
    //
    //
    // std::shared_ptr<ro::ubb::duck_app::domain::Duck> duck3 = std::make_shared<ro::ubb::duck_app::domain::Duck>(1, 7, 3);
    // duck_repository.update(std::static_pointer_cast<ro::ubb::duck_app::domain::Entity>(duck3));
    //
    // {
    // auto all_entities3 = duck_repository.findAll();
    // for (const auto &entity : all_entities3) {
    //     std::shared_ptr<ro::ubb::duck_app::domain::Duck> duck = std::dynamic_pointer_cast<ro::ubb::duck_app::domain::Duck>(entity);
    //     if (duck) {
    //         std::cout<<*duck<<std::endl;
    //     }
    //     }
    // }
    //
    // duck_repository.deleteById(1);
    //
    // auto all_entities2 = duck_repository.findAll();
    // // if (all_entities2.size() == 0) {std::cout<< "The repository is empty!"<<std::endl;}
    // if (all_entities2.empty()) {std::cout<<"The repository is empty!"<<std::endl;}
    // for (const auto &entity : all_entities2) {
    //     std::shared_ptr<ro::ubb::duck_app::domain::Duck> duck = std::dynamic_pointer_cast<ro::ubb::duck_app::domain::Duck>(entity);
    //     if (duck) {
    //         std::cout<<*duck<<std::endl;
    //     }
    // }






    // auto duck_validator = std::make_shared<ro::ubb::duck_app::domain::DuckValidator>();
    // std::string duck_file = "ducks.txt";
    // ro::ubb::duck_app::repository::FileRepository<ro::ubb::duck_app::domain::Duck> duck_repository(duck_validator, duck_file);
    // auto duck2 = std::make_shared<ro::ubb::duck_app::domain::Duck>(1, 5, 10);
    // duck_repository.save(duck2);
    // // duck_repository.save(std::static_pointer_cast<ro::ubb::duck_app::domain::Entity>(duck2));
    //
    // auto all_entities = duck_repository.findAll();
    // std::cout << "\n--- After Save ---\n";
    // for (const auto &entity : all_entities) {
    //     auto duck = std::dynamic_pointer_cast<ro::ubb::duck_app::domain::Duck>(entity);
    //     if (duck) {
    //         std::cout << *duck << std::endl;
    //     }
    // }
    //
    // // Update a duck
    // auto duck3 = std::make_shared<ro::ubb::duck_app::domain::Duck>(1, 7, 3);
    // duck_repository.update(duck3);
    //
    // // Display all ducks after update
    // std::cout << "\n--- After Update ---\n";
    // auto all_entities3 = duck_repository.findAll();
    // for (const auto &entity : all_entities3) {
    //     auto duck = std::dynamic_pointer_cast<ro::ubb::duck_app::domain::Duck>(entity);
    //     if (duck) {
    //         std::cout << *duck << std::endl;
    //     }
    // }
    //
    // // Delete duck
    // duck_repository.deleteById(1);
    //
    // // Display after delete
    // std::cout << "\n--- After Delete ---\n";
    // auto all_entities2 = duck_repository.findAll();
    // if (all_entities2.empty()) {
    //     std::cout << "The repository is empty!" << std::endl;
    // }
    // for (const auto &entity : all_entities2) {
    //     auto duck = std::dynamic_pointer_cast<ro::ubb::duck_app::domain::Duck>(entity);
    //     if (duck) {
    //         std::cout << *duck << std::endl;
    //     }
    // }





    // auto duck_validator = std::make_shared<ro::ubb::duck_app::domain::DuckValidator>();
    // ro::ubb::duck_app::repository::FileRepository file_repo(duck_validator, "ducks.txt");
    //
    // auto duck = std::make_shared<ro::ubb::duck_app::domain::Duck>(3, 10, 9);
    // file_repo.save(duck);
    //
    // auto all = file_repo.findAll();
    // for (const auto& entity : all) {
    //     auto d = std::dynamic_pointer_cast<ro::ubb::duck_app::domain::Duck>(entity);
    //     if (d) std::cout << *d << std::endl;
    // }







    // auto duck_validator = std::make_shared<ro::ubb::duck_app::domain::DuckValidator>();
    // std::shared_ptr<ro::ubb::duck_app::repository::Repository> duck_repository = std::make_shared<ro::ubb::duck_app::repository::FileRepository>(duck_validator, "ducks.txt");
    // ro::ubb::duck_app::service::DuckService duck_service(duck_repository);
    // duck_service.addDuck(5, 3, 5);
    // duck_service.addDuck(6, 5, 10);
    // std::vector<std::shared_ptr<ro::ubb::duck_app::domain::Duck>> ducks = duck_service.getDucks();
    // for (auto &duck : ducks) {
    //     std::cout << *duck;
    // }
    // duck_service.updateDuck(5, 10, 10);
    // std::vector<std::shared_ptr<ro::ubb::duck_app::domain::Duck>> ducks1 = duck_service.getDucks();
    // for (auto &duck : ducks1) {
    //     std::cout << *duck;
    // }
    //
    // duck_service.removeDuck(5);
    // std::vector<std::shared_ptr<ro::ubb::duck_app::domain::Duck>> ducks3 = duck_service.getDucks();
    // for (auto &duck : ducks3) {
    //     std::cout << *duck;
    // }
    //
    // auto lane_validator = std::make_shared<ro::ubb::duck_app::domain::LaneValidator>();
    // std::shared_ptr<ro::ubb::duck_app::repository::Repository> lane_repository = std::make_shared<ro::ubb::duck_app::repository::FileRepository>(lane_validator,"ducks.txt");
    // ro::ubb::duck_app::service::LaneService lane_service(lane_repository);
    // lane_service.addLane(9, 4);
    // lane_service.addLane(10, 5);
    // std::vector<std::shared_ptr<ro::ubb::duck_app::domain::Lane>> lanes = lane_service.getLanes();
    // for (auto &lane : lanes) {
    //     std::cout << *lane;
    // }





    auto duck_validator = std::make_shared<ro::ubb::duck_app::domain::DuckValidator>();
    auto duck_repository = std::make_shared<ro::ubb::duck_app::repository::FileRepository>(duck_validator, "ducks.txt");
    auto duck_service = std::make_shared<ro::ubb::duck_app::service::DuckService>(duck_repository);

    auto lane_validator = std::make_shared<ro::ubb::duck_app::domain::LaneValidator>();
    auto lane_repository = std::make_shared<ro::ubb::duck_app::repository::FileRepository>(lane_validator, "ducks.txt");
    auto lane_service = std::make_shared<ro::ubb::duck_app::service::LaneService>(lane_repository);

    auto reports_service = std::make_shared<ro::ubb::duck_app::service::ReportsService>(duck_repository, lane_repository);

    auto ui = std::make_shared<ro::ubb::duck_app::ui::UI>(duck_service, lane_service, reports_service);
    ui->runMenu();
    // reports_service->schemaMonti();

}
