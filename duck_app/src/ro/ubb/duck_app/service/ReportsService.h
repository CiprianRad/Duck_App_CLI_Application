//
// Created by cipri on 4/6/2025.
//

#ifndef REPORTSSERVICE_H
#define REPORTSSERVICE_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "../repository/Repository.h"
#include "../domain/Duck.h"
#include "../domain/Lane.h"

namespace ro::ubb::duck_app::service {

    class ReportsService {
    private:
        std::shared_ptr<ro::ubb::duck_app::repository::Repository> duck_repository;
        std::shared_ptr<ro::ubb::duck_app::repository::Repository> lane_repository;

        [[nodiscard]] std::unordered_map<int, std::shared_ptr<ro::ubb::duck_app::domain::Duck>> getAllDucks() const;
        [[nodiscard]] std::unordered_map<int, std::shared_ptr<ro::ubb::duck_app::domain::Lane>> getAllLanes() const;

    public:
        ReportsService(std::shared_ptr<ro::ubb::duck_app::repository::Repository> duck_repo,
                       std::shared_ptr<ro::ubb::duck_app::repository::Repository> lane_repo);
        virtual ~ReportsService() = default;

        [[nodiscard]] std::shared_ptr<ro::ubb::duck_app::repository::Repository> getDuckRepository() const;
        [[nodiscard]] std::shared_ptr<ro::ubb::duck_app::repository::Repository> getLaneRepository() const;

        void setDuckRepository(const std::shared_ptr<ro::ubb::duck_app::repository::Repository> &value);
        void setLaneRepository(const std::shared_ptr<ro::ubb::duck_app::repository::Repository> &value);

        void schemaMunti() const;
    };

}

#endif //REPORTSSERVICE_H