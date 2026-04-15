#include "DuckService.h"

namespace ro::ubb::duck_app::service {

    DuckService::DuckService(std::shared_ptr<ro::ubb::duck_app::repository::Repository> duck_repository) 
        : duck_repository(std::move(duck_repository)) {}

    std::shared_ptr<ro::ubb::duck_app::repository::Repository> DuckService::getDuckRepository() const {
        return duck_repository;
    }

    std::shared_ptr<ro::ubb::duck_app::domain::Duck> DuckService::findDuckById(int id) {
        auto entity = duck_repository->findById(id);
        if (entity) {
            return std::dynamic_pointer_cast<ro::ubb::duck_app::domain::Duck>(entity);
        }
        return nullptr;
    }

    std::vector<std::shared_ptr<ro::ubb::duck_app::domain::Duck>> DuckService::getDucks() {
        std::vector<std::shared_ptr<ro::ubb::duck_app::domain::Duck>> ducks;
        auto all_entities = duck_repository->findAll();
        
        ducks.reserve(all_entities.size());
        for (const auto &entity : all_entities) {
            if (auto duck = std::dynamic_pointer_cast<ro::ubb::duck_app::domain::Duck>(entity)) {
                ducks.push_back(duck);
            }
        }
        return ducks;
    }

    void DuckService::addDuck(int duck_id, int speed, int resistance) {
        auto duck = std::make_shared<ro::ubb::duck_app::domain::Duck>(duck_id, speed, resistance);
        duck_repository->save(duck); 
    }

    void DuckService::updateDuck(int duck_id, int speed, int resistance) {
        auto duck = std::make_shared<ro::ubb::duck_app::domain::Duck>(duck_id, speed, resistance);
        duck_repository->update(duck);
    }

    void DuckService::removeDuck(int id) {
        duck_repository->deleteById(id);
    }

}