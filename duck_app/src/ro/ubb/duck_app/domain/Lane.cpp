#include "Lane.h"

namespace ro::ubb::duck_app::domain {

    Lane::Lane() : lane_id(0), length(0) {}

    Lane::Lane(int lane_id, int length) : lane_id(lane_id), length(length) {}

    int Lane::getId() const {
        return lane_id;
    }

    int Lane::getLength() const {
        return length;
    }

    void Lane::setLane_id(int lane_id) {
        this->lane_id = lane_id;
    }

    void Lane::setLength(int length) {
        this->length = length;
    }

    std::ostream &operator<<(std::ostream &os, const Lane &lane) {
        os << "Lane ID: " << lane.lane_id << " Length: " << lane.length << std::endl;
        return os;
    }

    std::istream &operator>>(std::istream &is, Lane &lane) {
        std::cout << "Enter lane ID: ";
        is >> lane.lane_id;
        std::cout << "Enter Length: ";
        is >> lane.length;
        return is;
    }

}