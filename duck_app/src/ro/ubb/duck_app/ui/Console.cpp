#include "Console.h"
#include <iostream>

namespace ro::ubb::duck_app::ui {

    UI::UI(const std::shared_ptr<ro::ubb::duck_app::service::DuckService> &duck_service, 
           const std::shared_ptr<ro::ubb::duck_app::service::LaneService> &lane_service, 
           const std::shared_ptr<ro::ubb::duck_app::service::ReportsService> &reports_service) 
        : duck_service(duck_service), lane_service(lane_service), reports_service(reports_service) {}

    void UI::showAllOptions() {
        std::cout << "\nWelcome to the DuckApp!\nChoose an option:\n"
                  << "1. Duck options\n2. Lane options\n3. Reports options\nx. Exit\n";
    }

    void UI::showDuckOptions() {
        std::cout << "\n1. Add a duck\n2. Update a duck\n3. Delete a duck\n4. Show all ducks\nx. Back\n";
    }

    void UI::showLaneOptions() {
        std::cout << "\n1. Add a lane\n2. Update a lane\n3. Delete a lane\n4. Show all lanes\nx. Back\n";
    }

    void UI::showReportsOptions() {
        std::cout << "\n1. Show optimal time\nx. Back\n";
    }

    void UI::uiAddDuck() {
        int id, spd, res;
        std::cout << "Enter duck id: "; std::cin >> id;
        std::cout << "Enter speed: "; std::cin >> spd;
        std::cout << "Enter resistance: "; std::cin >> res;
        try {
            duck_service->addDuck(id, spd, res);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void UI::uiUpdateDuck() {
        int id, spd, res;
        std::cout << "Enter duck id: "; std::cin >> id;
        std::cout << "Enter new speed: "; std::cin >> spd;
        std::cout << "Enter new resistance: "; std::cin >> res;
        try {
            duck_service->updateDuck(id, spd, res);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void UI::uiDeleteDuck() {
        int id;
        std::cout << "Enter duck id to delete: "; std::cin >> id;
        try {
            duck_service->removeDuck(id);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void UI::uiShowAllDucks() {
        auto ducks = duck_service->getDucks();
        for (const auto& d : ducks) std::cout << *d;
    }

    void UI::uiAddLane() {
        int id, len;
        std::cout << "Enter lane id: "; std::cin >> id;
        std::cout << "Enter length: "; std::cin >> len;
        try {
            lane_service->addLane(id, len);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void UI::uiUpdateLane() {
        int id, len;
        std::cout << "Enter lane id: "; std::cin >> id;
        std::cout << "Enter new length: "; std::cin >> len;
        try {
            lane_service->updateLane(id, len);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void UI::uiDeleteLane() {
        int id;
        std::cout << "Enter lane id to delete: "; std::cin >> id;
        try {
            lane_service->removeLane(id);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void UI::uiShowAllLanes() {
        auto lanes = lane_service->getLanes();
        for (const auto& l : lanes) std::cout << *l;
    }

    void UI::uiShowOptimalTime() {
        reports_service->schemaMunti();
    }

    std::shared_ptr<ro::ubb::duck_app::service::DuckService> UI::getDuckService() const {
        return duck_service;
    }

    std::shared_ptr<ro::ubb::duck_app::service::LaneService> UI::getLaneService() const {
        return lane_service;
    }

    std::shared_ptr<ro::ubb::duck_app::service::ReportsService> UI::getReportsService() const {
        return reports_service;
    }

    void UI::setDuckService(const std::shared_ptr<ro::ubb::duck_app::service::DuckService> &duck_service) {
        this->duck_service = duck_service;
    }

    void UI::setLaneService(const std::shared_ptr<ro::ubb::duck_app::service::LaneService> &lane_service) {
        this->lane_service = lane_service;
    }

    void UI::setReportsService(const std::shared_ptr<ro::ubb::duck_app::service::ReportsService> &reports_service) {
        this->reports_service = reports_service;
    }

    void UI::runMenu() {
        char option;
        while (true) {
            showAllOptions();
            std::cout << "Option: "; std::cin >> option;
            if (option == 'x') break;

            if (option == '1') {
                while (true) {
                    showDuckOptions();
                    char sub; std::cin >> sub;
                    if (sub == 'x') break;
                    if (sub == '1') uiAddDuck();
                    else if (sub == '2') uiUpdateDuck();
                    else if (sub == '3') uiDeleteDuck();
                    else if (sub == '4') uiShowAllDucks();
                }
            } else if (option == '2') {
                while (true) {
                    showLaneOptions();
                    char sub; std::cin >> sub;
                    if (sub == 'x') break;
                    if (sub == '1') uiAddLane();
                    else if (sub == '2') uiUpdateLane();
                    else if (sub == '3') uiDeleteLane();
                    else if (sub == '4') uiShowAllLanes();
                }
            } else if (option == '3') {
                while (true) {
                    showReportsOptions();
                    char sub; std::cin >> sub;
                    if (sub == 'x') break;
                    if (sub == '1') uiShowOptimalTime();
                }
            }
        }
    }
}