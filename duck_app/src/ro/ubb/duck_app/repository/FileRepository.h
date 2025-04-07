//
// Created by cipri on 4/5/2025.
//

#ifndef FILEREPOSITORY_H
#define FILEREPOSITORY_H
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>
#include <iterator>

#include "..\domain\Duck.h"
#include "..\domain\Lane.h"
#include "..\domain\validators.h"
#include "Repository.h"


namespace ro::ubb::duck_app::repository {
    class FileRepositoryException : public domain::DuckAppException {
    public:
        using DuckAppException::DuckAppException;
    };

    class FileRepository : public Repository {
    private:
        std::string fileName;
        std::shared_ptr<domain::EntityValidator> validator;

        void loadData() {
            std::ifstream file(fileName);
            if (!file.is_open()) {
                throw FileRepositoryException("Could not open file :" + fileName);
            }

            std::string line;
            std::getline(file, line);
            std::istringstream firstLine(line);
            int duckCount, laneCount;
            firstLine >> duckCount >> laneCount;

            std::getline(file, line);
            std::istringstream speedStream(line);
            std::vector<int> speeds((std::istream_iterator<int>(speedStream)), {});

            std::getline(file,line);
            std::istringstream resistanceStream(line);
            std::vector<int> resistances((std::istream_iterator<int>(resistanceStream)), {});

            std::getline(file, line);
            std::istringstream lengthStream(line);
            std::vector<int> lengths((std::istream_iterator<int>(lengthStream)), {});

            if (speeds.size() != duckCount || resistances.size() != duckCount) {
                throw FileRepositoryException("Mismatch between the number of ducks and attributes given!");
            }

            if (lengths.size() != laneCount) {
                throw FileRepositoryException("Mismatch between the number of lanes and attributes given!");
            }

            if (std::dynamic_pointer_cast<domain::DuckValidator>(validator)) {
                for (int i = 0; i < duckCount; ++i) {
                    auto duck = std::make_shared<domain::Duck>(i + 1, speeds[i], resistances[i]);
                    Repository::save(duck);
                }
            }
            else if (std::dynamic_pointer_cast<domain::LaneValidator>(validator)) {
                for (int i = 0; i < laneCount; ++i) {
                    auto lane = std::make_shared<domain::Lane>(i + 1, lengths[i]);
                    Repository::save(lane);
                }
            }
        }
    public:
        explicit FileRepository(std::shared_ptr<domain::EntityValidator> validator, const std::string & file_name) : Repository(validator), fileName(file_name), validator(validator) { loadData();}
        void save(const std::shared_ptr<domain::Entity> & entity) override {
            Repository::save(entity);

            std::ifstream fileIn(fileName);
            std::string lines[4];
            for (int i = 0; i < 4 && std::getline(fileIn, lines[i]); i++);
            fileIn.close();
            int duckCount = 0; int laneCount = 0;
            std::istringstream header(lines[0]);
            header >> duckCount >> laneCount;

            std::ostringstream newContent;
            if (std::dynamic_pointer_cast<domain::Duck>(entity)) {
                ++duckCount;
                newContent << duckCount << " " << laneCount << "\n";

                lines[1] += (lines[1].empty() ? "" : " ") + std::to_string(std::dynamic_pointer_cast<domain::Duck>(entity)->getSpeed());
                lines[2] += (lines[2].empty() ? "" : " ") + std::to_string(std::dynamic_pointer_cast<domain::Duck>(entity)->getResistance());
            }
            else if (std::dynamic_pointer_cast<domain::Lane>(entity)) {
                ++laneCount;
                newContent << duckCount << " " << laneCount << "\n";
                lines[3] += (lines[3].empty() ? "" : " ") +std::to_string(std::dynamic_pointer_cast<domain::Lane>(entity)->getLength());
            }

            newContent << lines[1] << "\n" << lines[2] << "\n"<< lines[3] << "\n";

            std::ofstream fileOut(fileName);
            fileOut << newContent.str();
            fileOut.close();
        }
    };

    //TODO: Complete the FIleRepository with the delete and update options
    //TODO: Check the for loop at line 84. It may be useless.
}

#endif //FILEREPOSITORY_H



/*Note:  This is a templated version for the FileRepository which we will implement at a later time;
 * For the templated version we must change the Generic In Memory Repository.
 * This task is a to do in order to better understand templated versions.\
 * The reason behind not using templates is only to understand pointers and other C++ related syntax better
*/

// namespace ro::ubb::duck_app::repository {
//
//     class FileRepositoryException : public std::runtime_error {
//     public:
//         explicit FileRepositoryException(const std::string& message) :  std::runtime_error(message) {}
//     };
//
//     template <typename T>
//     class FileRepository : public Repository<T> {
//     private:
//         std::string file_name;
//         std::shared_ptr<domain::EntityValidator> validator;
//
//         std::vector<std::string> static split(const std::string& line) {
//             std::vector<std::string> tokens;
//             std::string token;
//             std::istringstream iss(line);
//             while (iss >> token) {
//                 tokens.push_back(token);
//             }
//             return tokens;
//         }
//
//         std::string static join(const std::vector<std::string>& tokens) {
//             std::ostringstream oss;
//             for (size_t i = 0; i < tokens.size(); i++) {
//                 if (i > 0) oss << " ";
//                 oss << tokens[i];
//             }
//             return oss.str();
//         }
//
//         std::vector<int> static parseLineToIntVector(const std::string& line) {
//             std::vector<int> result;
//             std::istringstream iss(line);
//             int value;
//             while (iss >> value) {
//                 result.push_back(value);
//             }
//             return result;
//         }
//
//         void loadData() {
//             std::ifstream file(file_name);
//             if (!file.is_open()) {
//                 throw FileRepositoryException("Could not open file " + file_name);
//             }
//
//             std::string line;
//             std::getline(file, line);
//             std::istringstream header_stream(line);
//             int n = 0, m = 0;
//             header_stream >> n >> m;
//
//             std::vector<int> speed_values, resistance_values, length_values;
//
//             // if (std::getline(file, line)) { speed_values.push_back(std::stoi(line)); }
//             if (std::getline(file, line)) { speed_values = parseLineToIntVector(line);}
//             if (std::getline(file, line)) { resistance_values = parseLineToIntVector(line);}
//             if (std::getline(file, line)) { length_values = parseLineToIntVector(line);}
//
//             if (std::dynamic_pointer_cast<domain::DuckValidator>(validator)) {
//                 if ((int)speed_values.size() != n || (int)resistance_values.size() != n) {
//                     throw FileRepositoryException ("Mismatch between the number of ducks and the number of attributes ");
//                 }
//                 for (int i = 0; i < n; i++) {
//                     auto duck = std::make_shared<domain::Duck>(i+1, speed_values[i], resistance_values[i]);
//                     Repository<T>.save(duck);
//                 }
//                 if ((int)length_values.size() != m) {
//                     throw FileRepositoryException ("Mismatch between the number of lanes and the number of attributes");
//                 }
//                 for (int i = 0; i < m; i++) {
//                     auto lane = std::make_shared<domain::Lane>(i+1, length_values[i]);
//                     Repository<T>.save(lane);
//                 }
//             }
//         }
//     public:
//         explicit FileRepository(const std::shared_ptr<domain::EntityValidator>& validator, const std::string &file) : Repository<T>(validator), validator(validator), file_name(file) {loadData();}
//         void save(const std::shared_ptr<T> &entity) {
//             Repository<T>.save(entity);
//
//             std::ifstream file(file_name);
//             std::vector<std::string> lines(4, "");
//
//             for (int i = 0; i < 4 && std::getline(file, lines[i]); i++) {
//
//                 std::vector<std::string> line1 = split(lines[0]);
//                 std::vector<std::string> line2 = split(lines[1]);
//                 std::vector<std::string> line3 = split(lines[2]);
//                 std::vector<std::string> line4 = split(lines[3]);
//
//                 int num_ducks = line1.empty() ? 0 : std::stoi(line1[0]);
//                 int num_lanes = line1.size() < 2 ? 0 : std::stoi(line1[1]);
//
//                 if (std::dynamic_pointer_cast<domain::Duck>(entity)) {
//                     num_ducks++;
//                     line1 = {std::to_string(num_ducks), std::to_string(num_lanes)};
//                     line2.push_back(std::to_string(std::dynamic_pointer_cast<domain::Duck>(entity)->getSpeed()));
//                     line3.push_back(std::to_string(std::dynamic_pointer_cast<domain::Duck>(entity)->getResistance()));
//                 }
//
//                 if (std::dynamic_pointer_cast<domain::Lane>(entity)) {
//                     num_lanes++;
//                     line1 = {std::to_string(num_ducks),  std::to_string(num_lanes)};
//                     line4.push_back(std::to_string(std::dynamic_pointer_cast<domain::Lane>(entity))->getLength());
//                 }
//
//                 std::ofstream out(file_name);
//                 out << join(line1) << "\n";
//                 out << join(line2) << "\n";
//                 out << join(line3) << "\n";
//                 out << join(line4) << "\n";
//
//             }
//
//         }
//     };
// }
