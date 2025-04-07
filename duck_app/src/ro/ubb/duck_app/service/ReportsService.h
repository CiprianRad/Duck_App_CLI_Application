//
// Created by cipri on 4/6/2025.
//

#ifndef REPORTSSERVICE_H
#define REPORTSSERVICE_H
#include <algorithm>
#include <memory>
#include <unordered_map>
#include "../repository/Repository.h"

namespace ro::ubb::duck_app::service {

    class ReportsService {
    private:
        std::shared_ptr<repository::Repository> duck_repository;
        std::shared_ptr<repository::Repository> lane_repository;

        [[nodiscard]] std::unordered_map<int, std::shared_ptr<domain::Duck>> getAllDucks() const  {
            std::unordered_map<int, std::shared_ptr<domain::Duck>> ducks;
            for (auto &entity : duck_repository->findAll()) {
                auto duck  = std::dynamic_pointer_cast<domain::Duck>(entity);
                ducks[duck->getId()] = duck;
            }
            return ducks;
        }

        [[nodiscard]] std::unordered_map<int, std::shared_ptr<domain::Lane>> getAllLane() const {
            std::unordered_map<int, std::shared_ptr<domain::Lane>> lanes;
            for (auto& entity : lane_repository->findAll()) {
                auto lane = std::dynamic_pointer_cast<domain::Lane>(entity);
                lanes[lane->getId()] = lane;
            }
            return lanes;
        }
    public:
        explicit ReportsService(const std::shared_ptr<repository::Repository> &duck_repository, const std::shared_ptr<repository::Repository> &lane_repository) : duck_repository(duck_repository), lane_repository(lane_repository) {}
        virtual ~ReportsService() = default;
        [[nodiscard]] std::shared_ptr<repository::Repository> getDuckRepository() const { return duck_repository;}
        [[nodiscard]] std::shared_ptr<repository::Repository> getLaneRepository() const { return lane_repository;}
        void setDuckRepository(const std::shared_ptr<repository::Repository> &value) { duck_repository = value;}
        void setLaneRepository(const std::shared_ptr<repository::Repository> &value) { lane_repository = value;}

        void schemaMunti() const {
            std::unordered_map<int, std::shared_ptr<domain::Duck>> ducks = getAllDucks();
            std::unordered_map<int, std::shared_ptr<domain::Lane>> lanes = getAllLane();


            std::vector<int> duck_ids;
            duck_ids.reserve(ducks.size());
            for (const auto& [duck_id, duck_ptr] : ducks) {
                duck_ids.push_back(duck_id);
            }

            // std::sort(duck_ids.begin(), duck_ids.end(), [&](int a, int b) {
            //     const auto& da = ducks.at(a);
            //     const auto& db = ducks.at(b);
            //     return std::tie(da->getResistance(), da->getSpeed()) < std::tie(db->getResistance(), db->getSpeed());
            // });

            std::sort(duck_ids.begin(), duck_ids.end(), [&](int a, int b) {
                const auto& duck1 = ducks.at(a);
                const auto& duck2 = ducks.at(b);
                return std::make_tuple(duck1->getResistance(), duck1->getSpeed()) < std::make_tuple(duck2->getResistance(), duck2->getSpeed());
            });


            std::vector<int> lane_ids;
            lane_ids.reserve(lanes.size());
            for (const auto &key_value : lanes) {
                lane_ids.push_back(key_value.first);
            }

            std::sort(lane_ids.begin(), lane_ids.end(), [&](int a, int b) {
                const auto& lane1 = lanes.at(a);
                const auto& lane2 = lanes.at(b);
                return lane1->getLength() < lane2->getLength();
            });


            std::size_t numberOfDucks = duck_ids.size();
            std::size_t numberOfLanes = lane_ids.size();
            std::vector<long double> times(numberOfLanes, 0.0L);

            for (std::size_t j = 0; j < numberOfDucks; j++) {
                if (j < numberOfLanes) {
                    int duck_id = duck_ids[j];
                    int lane_id = lane_ids[j];
                    // double lane_length = static_cast<double>(lanes[lane_id]->getLength());
                    // double duck_speed = static_cast<double>(ducks[duck_id]->getSpeed());
                    auto lane_length = static_cast<long double>(lanes[lane_id]->getLength());
                    auto duck_speed = static_cast<long double>(ducks[duck_id]->getSpeed());
                    long double time = lane_length / duck_speed;

                    if (j == 0 || times[j - 1] < time) {
                        times[j] = time;
                    }
                    else {
                        times[j] = times[j - 1];
                    }
                }
                std::size_t upper = j;
                std::size_t lower = 0;
                if (numberOfLanes < j) {
                    upper = numberOfLanes;
                }
                if (numberOfDucks - numberOfLanes <= j) {
                    lower = j - numberOfDucks + numberOfLanes;
                }

                // for (std::size_t i = upper; i >= lower; i--)
                for (std::size_t i = upper; i-- > lower;) {
                    int duck_id = duck_ids[j];
                    int lane_id = lane_ids[i];
                    auto lane_length = static_cast<long double>(lanes[lane_id]->getLength());
                    auto duck_speed = static_cast<long double>(ducks[duck_id]->getSpeed());
                    long double time = lane_length / duck_speed;

                    if (i > 0 && times[i - 1] > time) {
                        time = times[i - 1];
                    }

                    if (time < times[i]) {
                        times[i] = time;
                    }

                }
            }
            std::cout << std::fixed << std::setprecision(20);
            std::cout << "Minimum time is: " << times[numberOfLanes - 1] * 2 << std::endl;
        }
    };

    // TODO: Change the dict[key] to dict.at(key) because C++ doesn't have a KeyError implemented and it will automatically add the element with the key and value given.

}


#endif //REPORTSSERVICE_H
