//
// Created by cipri on 4/5/2025.
//

#ifndef DUCKSERVICE_H
#define DUCKSERVICE_H

#include <memory>
#include <vector>
#include "../domain/Duck.h"
#include "../repository/Repository.h"

namespace ro::ubb::duck_app::service {

    class DuckService {
    private:
        std::shared_ptr<repository::Repository> duck_repository;

    public:
        explicit DuckService(std::shared_ptr<repository::Repository> duck_repository);

        [[nodiscard]] std::shared_ptr<repository::Repository> getDuckRepository() const;

        std::shared_ptr<domain::Duck> findDuckById(int id);
        std::vector<std::shared_ptr<domain::Duck>> getDucks();

        void addDuck(int duck_id, int speed, int resistance);
        void updateDuck(int duck_id, int speed, int resistance);
        void removeDuck(int id);
    };

}

#endif //DUCKSERVICE_H