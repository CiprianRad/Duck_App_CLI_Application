#ifndef LINE_H
#define LINE_H

#include <iostream>

namespace ro::ubb::duck_app::domain {
    class Lane : public Entity {
    private:
        int lane_id;
        int length;
    public:
        Lane() {this->lane_id = 0; this->length = 0;}
        explicit Lane(int lane_id, int length) : lane_id(lane_id), length(length) {}
        ~Lane() override = default;
        [[nodiscard]] int getId() const override { return lane_id; }
        [[nodiscard]] int getLength() const { return length; }
        void setLane_id(int lane_id) { auto &id = this->lane_id; id = lane_id;}
        void setLength(int length) { auto &lane_length = this->length; lane_length = length; }
        friend std::ostream &operator<<(std::ostream &os, const Lane &lane) { std::cout << "Lane ID: " << lane.getId() << " Length: " << lane.getLength() << std::endl; return os;}
        friend std::istream &operator>>(std::istream &is, Lane &lane) {int lane_id; std::cout << "Enter lane ID: "; is >> lane_id; lane.setLane_id(lane_id); int length; std::cout << "Enter Length: "; is >> length; lane.setLength(length); return is;}
    };
}

#endif //LINE_H
