//
// Created by cipri on 4/6/2025.
//
#ifndef CONSOLE_H
#define CONSOLE_H

#include "../service/DuckService.h"
#include "../service/LaneService.h"
#include "../service/ReportsService.h"
#include <memory>

namespace ro::ubb::duck_app::ui {

    class UI {
    private:
        std::shared_ptr<service::DuckService> duck_service;
        std::shared_ptr<service::LaneService> lane_service;
        std::shared_ptr<service::ReportsService> reports_service;

        void uiAddDuck();
        void uiUpdateDuck();
        void uiDeleteDuck();
        void uiShowAllDucks();

        void uiAddLane();
        void uiUpdateLane();
        void uiDeleteLane();
        void uiShowAllLanes();

        void uiShowOptimalTime();

        static void showAllOptions();
        static void showDuckOptions();
        static void showLaneOptions();
        static void showReportsOptions();

    public:
        explicit UI(const std::shared_ptr<service::DuckService> &duck_service,
                    const std::shared_ptr<service::LaneService> &lane_service,
                    const std::shared_ptr<service::ReportsService> &reports_service);
        ~UI() = default;

        // Getters and Setters
        [[nodiscard]] std::shared_ptr<service::DuckService> getDuckService() const;
        [[nodiscard]] std::shared_ptr<service::LaneService> getLaneService() const;
        [[nodiscard]] std::shared_ptr<service::ReportsService> getReportsService() const;

        void setDuckService(const std::shared_ptr<service::DuckService> &duck_service);
        void setLaneService(const std::shared_ptr<service::LaneService> &lane_service);
        void setReportsService(const std::shared_ptr<service::ReportsService> &reports_service);

        void runMenu();
    };
}

#endif //CONSOLE_H
