//
// Created by cipri on 4/6/2025.
//

#ifndef CONSOLE_H
#define CONSOLE_H

#include "../service/DuckService.h"
#include "../service/LaneService.h"
#include "../service/ReportsService.h"
#include <iostream>

namespace ro::ubb::duck_app::ui {
    class UI {
    private:
        std::shared_ptr<service::DuckService> duck_service;
        std::shared_ptr<service::LaneService> lane_service;
        std::shared_ptr<service::ReportsService> reports_service;

    public:
        explicit UI(const std::shared_ptr<service::DuckService> &duck_service, const std::shared_ptr<service::LaneService> &lane_service, const std::shared_ptr<service::ReportsService> &reports_service) : duck_service(duck_service), lane_service(lane_service), reports_service(reports_service) {}
        ~UI() = default;
        [[nodiscard]] std::shared_ptr<service::DuckService> getDuckService() const {return duck_service;}
        [[nodiscard]] std::shared_ptr<service::LaneService> getLaneService() const {return lane_service;}
        [[nodiscard]] std::shared_ptr<service::ReportsService> getReportsService() const {return reports_service;}
        void setDuckService(const std::shared_ptr<service::DuckService> &duck_service) {this->duck_service = duck_service;}
        void setLaneService(const std::shared_ptr<service::LaneService> &lane_service) {this->lane_service = lane_service;}
        void setReportsService(const std::shared_ptr<service::ReportsService> &reports_service) {this->reports_service = reports_service;}

        static void showAllOptions() {
            std::cout << "Welcome to the DuckApp! " << std::endl;
            std::cout << "Choose an option from below!" << std::endl;
            std::cout << "1.Go to duck options" << std::endl;
            // std::cout << "1.Add a duck" << std::endl;
            // std::cout << "2.Update a duck" << std::endl;
            // std::cout << "3.Delete a duck" << std::endl;
            // std::cout << "4.Show all ducks" << std::endl;
            std::cout << "2.Go to lane options" << std::endl;
            // std::cout << "5.Add a lane" << std::endl;
            // std::cout << "6.Update a lane"  << std::endl;
            // std::cout << "7.Delete a lane" << std::endl;
            // std::cout << "8.Show all lanes" << std::endl;
            std::cout << "3.Go to reports options" << std::endl;
            // std::cout << "9.Show optimal time" << std::endl;
            std::cout << "x. Exit" << std::endl;

        }

        static void showDuckOptions() {
            std::cout << "1.Add a duck" << std::endl;
            std::cout << "2.Update a duck" << std::endl;
            std::cout << "3.Delete a duck" << std::endl;
            std::cout << "4.Show all ducks" << std::endl;
            std::cout << "x. Exit" << std::endl;
        }

        static void showLaneOptions() {
            std::cout << "1.Add a lane" << std::endl;
            std::cout << "2.Update a lane"  << std::endl;
            std::cout << "3.Delete a lane" << std::endl;
            std::cout << "4.Show all lanes" << std::endl;
            std::cout << "x. Exit" << std::endl;
        }

        static void showReportsOptions() {
            std::cout << "1.Show optimal time" << std::endl;
            std::cout << "x. Exit" << std::endl;
        }


        void uiAddDuck() {
            int duck_id = -1;
            int speed = -1;
            int resistance = -1;
            try {
                std::cout << "Enter duck id: ";
                std::cin >> duck_id;
                std::cout << "Enter speed: ";
                std::cin >> speed;
                std::cout << "Enter resistance: ";
                std::cin >> resistance;
                try {
                    duck_service->addDuck(duck_id, speed, resistance);
                } catch (repository::RepositoryException &re) {
                    std::cout << "Duck with this ID already exists" << re.what() << std::endl;
                }
            } catch (domain::ValidatorException &ve) {
                std::cerr << "Invalid inputs" << ve.what() << std::endl;
            }
        }

        void uiUpdateDuck() {
            int duck_id = -1;
            int speed = -1;
            int resistance = -1;
            try {
                std::cout << "Enter duck id: ";
                std::cin >> duck_id;
                std::cout << "Enter speed: ";
                std::cin >> speed;
                std::cout << "Enter resistance: ";
                std::cin >> resistance;
                try {
                    duck_service->updateDuck(duck_id, speed, resistance);
                } catch (repository::RepositoryException &re) {
                    std::cerr << "Duck with this id does not exist " << re.what() << std::endl;
                }
            } catch (domain::ValidatorException &ve) {
                std::cerr << "Invalid inputs" << ve.what() << std::endl;
            }
        }

        void uiDeleteDuck() {
            int duck_id = -1;
            try {
                std::cout << "Enter duck id: ";
                std::cin >> duck_id;
                try {
                    duck_service->removeDuck(duck_id);
                } catch (repository::RepositoryException &re) {
                    std::cerr << "Duck with this id does not exist " << re.what() << std::endl;
                }
            } catch (domain::ValidatorException &ve) {
                std::cerr << "Invalid inputs" << ve.what() << std::endl;
            }
        }

        void uiShowAllDucks() {
            std::vector<std::shared_ptr<domain::Duck>> ducks = duck_service->getDucks();
            for (auto& duck : ducks) {
                std::cout << *duck;
            }
        }


        void uiAddLane() {
            int lane_id = -1;
            int length = -1;
            try {
                std::cout << "Enter lane id: ";
                std::cin >> lane_id;
                std::cout << "Enter length: ";
                std::cin >> length;
                try {
                    lane_service->addLane(lane_id, length);
                } catch (repository::RepositoryException &re) {
                    std::cerr << "Lane with this ID already exists" << re.what() << std::endl;
                }
            } catch (domain::ValidatorException &ve) {
                std::cerr << "Invalid inputs" << ve.what() << std::endl;
            }
        }

        void uiUpdateLane() {
            int lane_id = -1;
            int length = -1;
            try {
                std::cout << "Enter lane id: ";
                std::cin >> lane_id;
                std::cout << "Enter length: ";
                std::cin >> length;
                try {
                    lane_service->updateLane(lane_id, length);
                } catch (repository::RepositoryException &re) {
                    std::cerr << "Lane with this ID does not exist" << re.what() << std::endl;
                }
            }catch (domain::ValidatorException &ve) {
                std::cerr << "Invalid inputs" << ve.what() << std::endl;
            }
        }

        void uiDeleteLane() {
            int lane_id = -1;
            int length = -1;
            try {
                std::cout << "Enter lane id: ";
                std::cin >> lane_id;
                std::cout << "Enter length: ";
                std::cin >> length;
                try {
                    lane_service->removeLane(lane_id);
                } catch (repository::RepositoryException &re) {
                    std::cerr << "Lane with this ID does not exist " << re.what() << std::endl;
                }
            } catch (domain::ValidatorException &ve) {
                std::cerr << "Invalid inputs" << ve.what() <<std::endl;
            }
        }

        void uiShowAllLanes() {
            std::vector<std::shared_ptr<domain::Lane>> lanes = lane_service->getLanes();
            for (auto& lane : lanes) {
                std::cout << *lane;
            }
        }

        void uiShowOptimalTime() {
            reports_service->schemaMunti();
        }

        // void runMenu() {
        //     do {
        //         showAllOptions();
        //         try{
        //             char option = '';
        //             std::cout << "Enter your option: ";
        //             std::cin >> option;
        //
        //             if (option == '1') {
        //                 showDuckOptions();
        //                 try {
        //                     char duck_option = '';
        //                     std::cout << "Enter your option: ";
        //                     std::cin >> duck_option;
        //                     if (duck_option == '1') {
        //                         uiAddDuck();
        //                         continue;
        //                     }
        //                     if (duck_option == '2') {
        //                         uiUpdateDuck();
        //                         continue;
        //                     }
        //                     if (duck_option == '3') {
        //                         uiDeleteDuck();
        //                         continue;
        //                     }
        //                     if (duck_option == '4') {
        //                         uiShowAllDucks();
        //                         continue;
        //                     }
        //                     if (duck_option == 'x') {
        //                         break;
        //                     }
        //                 }
        //                 catch (const std::out_of_range &e) {
        //                     std::cerr << "Option not implemented " << e.what() << std::endl;
        //                 }
        //             }
        //             if (option == '2') {
        //                 showLaneOptions();
        //                 try{
        //                     char lane_option = '';
        //                     std::cout << "Enter your option: ";
        //                     std::cin >> lane_option;
        //
        //                     if (lane_option == '1') {
        //                         uiAddLane();
        //                         continue;
        //                     }
        //                     if (lane_option == '2') {
        //                         uiUpdateLane();
        //                         continue;
        //                     }
        //                     if (lane_option == '3') {
        //                         uiDeleteLane();
        //                         continue;
        //                     }
        //                     if (lane_option == '4') {
        //                         uiShowAllLanes();
        //                         continue;
        //                     }
        //                     if (lane_option == 'x') {
        //                         break;
        //                     }
        //                 }
        //                 catch (const std::out_of_range &e) {
        //                     std::cerr << "Option not implemented " << e.what() << std::endl;
        //                 }
        //             }
        //             if (option == '3') {
        //                 showReportsOptions();
        //                 try {
        //                     char reports_option = '';
        //                     std::cout << "Enter your option: ";
        //                     std::cin >> reports_option;
        //                     if (reports_option == '1') {
        //                         uiShowOptimalTime();
        //                         continue;
        //                     }
        //                     if (reports_option == 'x') {
        //                         break;
        //                     }
        //                 }
        //                 catch (const std::out_of_range &e) {
        //                     std::cerr << "Option not implemented " << e.what() << std::endl;
        //                 }
        //             }
        //         }
        //         catch (const std::exception &e) {
        //             std::cerr << "Option not implemented " << e.what() << std::endl;
        //         }
        //     }
        //     while (true);
        // }


        void runMenu() {
            while (true) {
                showAllOptions();
                try {
                    char option = '\0';
                    std::cout << "Enter your option: ";
                    std::cin >> option;

                    if (option == '1') {
                        while (true) {
                            showDuckOptions();
                            try {
                                char duck_option = '\0';
                                std::cout << "Enter your option: ";
                                std::cin >> duck_option;

                                if (duck_option == '1') {
                                    uiAddDuck();
                                } else if (duck_option == '2') {
                                    uiUpdateDuck();
                                } else if (duck_option == '3') {
                                    uiDeleteDuck();
                                } else if (duck_option == '4') {
                                    uiShowAllDucks();
                                } else if (duck_option == 'x') {
                                    break;
                                } else {
                                    std::cerr << "Invalid option in duck menu.\n";
                                }
                            } catch (const std::out_of_range &e) {
                                std::cerr << "Option not implemented " << e.what() << std::endl;
                            }
                        }
                    } else if (option == '2') {
                        while (true) {
                            showLaneOptions();
                            try {
                                char lane_option = '\0';
                                std::cout << "Enter your option: ";
                                std::cin >> lane_option;

                                if (lane_option == '1') {
                                    uiAddLane();
                                } else if (lane_option == '2') {
                                    uiUpdateLane();
                                } else if (lane_option == '3') {
                                    uiDeleteLane();
                                } else if (lane_option == '4') {
                                    uiShowAllLanes();
                                } else if (lane_option == 'x') {
                                    break;
                                } else {
                                    std::cerr << "Invalid option in lane menu.\n";
                                }
                            } catch (const std::out_of_range &e) {
                                std::cerr << "Option not implemented " << e.what() << std::endl;
                            }
                        }
                    } else if (option == '3') {
                        while (true) {
                            showReportsOptions();
                            try {
                                char reports_option = '\0';
                                std::cout << "Enter your option: ";
                                std::cin >> reports_option;

                                if (reports_option == '1') {
                                    uiShowOptimalTime();
                                } else if (reports_option == 'x') {
                                    break;
                                } else {
                                    std::cerr << "Invalid option in reports menu.\n";
                                }
                            } catch (const std::out_of_range &e) {
                                std::cerr << "Option not implemented " << e.what() << std::endl;
                            }
                        }
                    } else if (option == 'x') {
                        break;
                    } else {
                        std::cerr << "Invalid main menu option.\n";
                    }
                } catch (const std::exception &e) {
                    std::cerr << "Option not implemented " << e.what() << std::endl;
                }
            }
        }
    };
}

#endif //CONSOLE_H
