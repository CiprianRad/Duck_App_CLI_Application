#include "FileRepository.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

namespace ro::ubb::duck_app::repository {

    FileRepository::FileRepository(std::shared_ptr<domain::EntityValidator> validator, const std::string& fileName)
        : Repository(validator), fileName(fileName), validator(validator) {
        loadData();
    }

    void FileRepository::loadData() {
        std::ifstream file(fileName);
        if (!file.is_open()) return;

        std::string line;
        if (!std::getline(file, line)) return;

        std::istringstream firstLine(line);
        int duckCount, laneCount;
        if (!(firstLine >> duckCount >> laneCount)) return;

        auto readInts = [&](std::vector<int>& vec) {
            if (std::getline(file, line)) {
                std::istringstream iss(line);
                vec.assign(std::istream_iterator<int>(iss), std::istream_iterator<int>());
            }
        };

        std::vector<int> speeds, resistances, lengths;
        readInts(speeds);
        readInts(resistances);
        readInts(lengths);

        if (std::dynamic_pointer_cast<domain::DuckValidator>(validator)) {
            for (size_t i = 0; i < speeds.size() && i < resistances.size(); ++i) {
                Repository::save(std::make_shared<domain::Duck>(static_cast<int>(i + 1), speeds[i], resistances[i]));
            }
        } else if (std::dynamic_pointer_cast<domain::LaneValidator>(validator)) {
            for (size_t i = 0; i < lengths.size(); ++i) {
                Repository::save(std::make_shared<domain::Lane>(static_cast<int>(i + 1), lengths[i]));
            }
        }
    }

    void FileRepository::saveToFile() {
        auto allEntities = findAll();
        std::vector<std::shared_ptr<domain::Duck>> ducks;
        std::vector<std::shared_ptr<domain::Lane>> lanes;

        for (const auto& entity : allEntities) {
            if (auto d = std::dynamic_pointer_cast<domain::Duck>(entity)) ducks.push_back(d);
            else if (auto l = std::dynamic_pointer_cast<domain::Lane>(entity)) lanes.push_back(l);
        }

        std::ofstream file(fileName);
        file << ducks.size() << " " << lanes.size() << "\n";

        for (size_t i = 0; i < ducks.size(); ++i) file << ducks[i]->getSpeed() << (i == ducks.size() - 1 ? "" : " ");
        file << "\n";
        for (size_t i = 0; i < ducks.size(); ++i) file << ducks[i]->getResistance() << (i == ducks.size() - 1 ? "" : " ");
        file << "\n";

        for (size_t i = 0; i < lanes.size(); ++i) file << lanes[i]->getLength() << (i == lanes.size() - 1 ? "" : " ");
        file << "\n";
    }

    void FileRepository::save(const std::shared_ptr<domain::Entity>& entity) {
        Repository::save(entity);
        saveToFile();
    }

    void FileRepository::update(const std::shared_ptr<domain::Entity>& entity) {
        Repository::update(entity);
        saveToFile();
    }

    void FileRepository::deleteById(int id) {
        Repository::deleteById(id);
        saveToFile();
    }
}