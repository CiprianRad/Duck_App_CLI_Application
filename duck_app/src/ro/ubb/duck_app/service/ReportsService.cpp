#include "ReportsService.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <tuple>

namespace ro::ubb::duck_app::service {

    ReportsService::ReportsService(std::shared_ptr<repository::Repository> duck_repo, 
                                   std::shared_ptr<repository::Repository> lane_repo)
        : duck_repository(std::move(duck_repo)), lane_repository(std::move(lane_repo)) {}

    std::unordered_map<int, std::shared_ptr<domain::Duck>> ReportsService::getAllDucks() const {
        std::unordered_map<int, std::shared_ptr<domain::Duck>> ducks;
        for (const auto &entity : duck_repository->findAll()) {
            if (auto duck = std::dynamic_pointer_cast<domain::Duck>(entity)) {
                ducks[duck->getId()] = duck;
            }
        }
        return ducks;
    }

    std::unordered_map<int, std::shared_ptr<domain::Lane>> ReportsService::getAllLanes() const {
        std::unordered_map<int, std::shared_ptr<domain::Lane>> lanes;
        for (const auto& entity : lane_repository->findAll()) {
            if (auto lane = std::dynamic_pointer_cast<domain::Lane>(entity)) {
                lanes[lane->getId()] = lane;
            }
        }
        return lanes;
    }

    std::shared_ptr<repository::Repository> ReportsService::getDuckRepository() const { return duck_repository; }
    std::shared_ptr<repository::Repository> ReportsService::getLaneRepository() const { return lane_repository; }
    
    void ReportsService::setDuckRepository(const std::shared_ptr<repository::Repository> &value) { duck_repository = value; }
    void ReportsService::setLaneRepository(const std::shared_ptr<repository::Repository> &value) { lane_repository = value; }

    void ReportsService::schemaMunti() const {
        auto ducks = getAllDucks();
        auto lanes = getAllLanes();

        if (ducks.empty() || lanes.empty()) {
            std::cout << "Insufficient data for report.\n";
            return;
        }

        std::vector<int> duck_ids;
        duck_ids.reserve(ducks.size());
        for (const auto& [id, _] : ducks) duck_ids.push_back(id);

        std::sort(duck_ids.begin(), duck_ids.end(), [&](int a, int b) {
            const auto& d1 = ducks.at(a);
            const auto& d2 = ducks.at(b);
            return std::tie(d1->getResistance(), d1->getSpeed()) < std::tie(d2->getResistance(), d2->getSpeed());
        });

        std::vector<int> lane_ids;
        lane_ids.reserve(lanes.size());
        for (const auto& [id, _] : lanes) lane_ids.push_back(id);

        std::sort(lane_ids.begin(), lane_ids.end(), [&](int a, int b) {
            return lanes.at(a)->getLength() < lanes.at(b)->getLength();
        });

        std::size_t numDucks = duck_ids.size();
        std::size_t numLanes = lane_ids.size();
        std::vector<long double> times(numLanes, 0.0L);

        for (std::size_t j = 0; j < numDucks; j++) {
            if (j < numLanes) {
                auto lane_len = static_cast<long double>(lanes.at(lane_ids[j])->getLength());
                auto duck_spd = static_cast<long double>(ducks.at(duck_ids[j])->getSpeed());
                long double time = lane_len / duck_spd;

                times[j] = (j == 0) ? time : std::max(times[j - 1], time);
            }

            std::size_t upper = std::min(j, numLanes - 1);
            std::size_t lower = (numDucks <= numLanes) ? 0 : (j >= (numDucks - numLanes) ? (j - (numDucks - numLanes)) : 0);

            for (std::size_t i = upper; i-- > lower;) {
                auto lane_len = static_cast<long double>(lanes.at(lane_ids[i])->getLength());
                auto duck_spd = static_cast<long double>(ducks.at(duck_ids[j])->getSpeed());
                long double time = lane_len / duck_spd;

                if (i > 0) time = std::max(time, times[i - 1]);
                times[i] = std::min(times[i], time);
            }
        }

        std::cout << std::fixed << std::setprecision(20);
        std::cout << "Minimum time is: " << times[numLanes - 1] * 2 << std::endl;
    }

    // TODO: Change the dict[key] to dict.at(key) because C++ doesn't have a KeyError implemented and it will automatically add the element with the key and value given.

}