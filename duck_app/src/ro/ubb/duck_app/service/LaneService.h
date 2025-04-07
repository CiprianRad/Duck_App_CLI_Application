//
// Created by cipri on 4/5/2025.
//

#ifndef LANESERVICE_H
#define LANESERVICE_H

#include <memory>
#include <vector>

#include "../repository/Repository.h"

namespace ro::ubb::duck_app::service {
    class LaneService {
    private:
        std::shared_ptr<repository::Repository> lane_repository;
    public:
        explicit LaneService(std::shared_ptr<repository::Repository> lane_repository) : lane_repository(lane_repository) {}
        virtual ~LaneService() = default;
        [[nodiscard]] std::shared_ptr<repository::Repository> getRepository() const { return lane_repository;}

        void addLane(int lane_id, int length) {
            auto lane = std::make_shared<domain::Lane>(lane_id, length);
            lane_repository->save(lane);
        }

        void updateLane(int lane_id, int length) {
            auto lane = std::make_shared<domain::Lane>(lane_id, length);
            lane_repository->update(lane);
        }

        void removeLane(int lane_id) {
            lane_repository->deleteById(lane_id);
        }

        std::shared_ptr<domain::Lane> findLaneById(int lane_id) {
            auto entity = lane_repository->findById(lane_id);
            if (entity) {
                return std::dynamic_pointer_cast<domain::Lane>(entity);
            }
            return nullptr;
        }

        std::vector<std::shared_ptr<domain::Lane>> getLanes() {
            std::vector<std::shared_ptr<domain::Lane>> lanes;
            auto all_entities = lane_repository->findAll();
            for (const auto &entity : all_entities) {
                auto lane = std::dynamic_pointer_cast<domain::Lane>(entity);
                if (lane) {
                    lanes.emplace_back(lane);
                }
            }
            return lanes;
        }
    };
}
#endif //LANESERVICE_H
