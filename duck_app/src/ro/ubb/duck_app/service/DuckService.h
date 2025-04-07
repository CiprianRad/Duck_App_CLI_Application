//
// Created by cipri on 4/5/2025.
//

#ifndef DUCKSERVICE_H
#define DUCKSERVICE_H
#include <memory>
#include <vector>

#include "../domain/Duck.h"

namespace ro::ubb::duck_app::service {
    class DuckService {
    private:
        std::shared_ptr<repository::Repository> duck_repository;
    public:

        explicit DuckService(std::shared_ptr<repository::Repository> duck_repository) : duck_repository(duck_repository) {}
        [[nodiscard]] std::shared_ptr<repository::Repository> getDuckRepository() const {return duck_repository;}

        std::shared_ptr<domain::Duck> findDuckById(int id) {
            auto entity = duck_repository->findById(id);
            if (entity) {
                return std::dynamic_pointer_cast<domain::Duck>(entity);
            }
            return nullptr;
        }

        std::vector<std::shared_ptr<domain::Duck>> getDucks() {
            std::vector<std::shared_ptr<domain::Duck>> ducks;
            auto all_entities = duck_repository->findAll();
            for (const auto &entity : all_entities) {
                auto duck = std::dynamic_pointer_cast<domain::Duck>(entity);
                if (duck) {
                    ducks.emplace_back(duck);
                }
            }
            return ducks;
        }

        void addDuck(int duck_id, int speed, int resistance) {
            auto duck = std::make_shared<domain::Duck>(duck_id, speed, resistance);
            duck_repository->save(std::static_pointer_cast<domain::Entity>(duck));
        }

        void updateDuck(int duck_id, int speed, int resistance) {
            auto duck = std::make_shared<domain::Duck>(duck_id, speed, resistance);
            duck_repository->update(std::static_pointer_cast<domain::Entity>(duck));
        }

        void removeDuck(int id) {
            duck_repository->deleteById(id);
        }
    };
}



#endif //DUCKSERVICE_H
