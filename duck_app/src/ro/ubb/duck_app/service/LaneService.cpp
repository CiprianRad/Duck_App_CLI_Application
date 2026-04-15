#include "LaneService.h"

namespace ro::ubb::duck_app::service {

    LaneService::LaneService(std::shared_ptr<ro::ubb::duck_app::repository::Repository> lane_repository) 
        : lane_repository(std::move(lane_repository)) {}

    std::shared_ptr<ro::ubb::duck_app::repository::Repository> LaneService::getRepository() const {
        return lane_repository;
    }

    void LaneService::addLane(int lane_id, int length) {
        auto lane = std::make_shared<ro::ubb::duck_app::domain::Lane>(lane_id, length);
        lane_repository->save(lane);
    }

    void LaneService::updateLane(int lane_id, int length) {
        auto lane = std::make_shared<ro::ubb::duck_app::domain::Lane>(lane_id, length);
        lane_repository->update(lane);
    }

    void LaneService::removeLane(int lane_id) {
        lane_repository->deleteById(lane_id);
    }

    std::shared_ptr<ro::ubb::duck_app::domain::Lane> LaneService::findLaneById(int lane_id) {
        auto entity = lane_repository->findById(lane_id);
        if (entity) {
            return std::dynamic_pointer_cast<ro::ubb::duck_app::domain::Lane>(entity);
        }
        return nullptr;
    }

    std::vector<std::shared_ptr<ro::ubb::duck_app::domain::Lane>> LaneService::getLanes() {
        std::vector<std::shared_ptr<ro::ubb::duck_app::domain::Lane>> lanes;
        auto all_entities = lane_repository->findAll();
        
        lanes.reserve(all_entities.size());
        for (const auto &entity : all_entities) {
            if (auto lane = std::dynamic_pointer_cast<ro::ubb::duck_app::domain::Lane>(entity)) {
                lanes.push_back(lane);
            }
        }
        return lanes;
    }

}