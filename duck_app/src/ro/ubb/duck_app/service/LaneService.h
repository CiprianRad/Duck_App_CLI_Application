//
// Created by cipri on 4/5/2025.
//
#ifndef LANESERVICE_H
#define LANESERVICE_H

#include <memory>
#include <vector>
#include "../domain/Lane.h"
#include "../repository/Repository.h"

namespace ro::ubb::duck_app::service {

    class LaneService {
    private:
        std::shared_ptr<ro::ubb::duck_app::repository::Repository> lane_repository;

    public:
        explicit LaneService(std::shared_ptr<ro::ubb::duck_app::repository::Repository> lane_repository);
        virtual ~LaneService() = default;

        [[nodiscard]] std::shared_ptr<ro::ubb::duck_app::repository::Repository> getRepository() const;

        void addLane(int lane_id, int length);
        void updateLane(int lane_id, int length);
        void removeLane(int lane_id);

        std::shared_ptr<ro::ubb::duck_app::domain::Lane> findLaneById(int lane_id);
        std::vector<std::shared_ptr<ro::ubb::duck_app::domain::Lane>> getLanes();
    };

}

#endif //LANESERVICE_H