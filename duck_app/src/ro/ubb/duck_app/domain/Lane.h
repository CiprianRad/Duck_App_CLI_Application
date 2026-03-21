#ifndef LANE_H
#define LANE_H

#include <iostream>
#include "Duck.h"

namespace ro::ubb::duck_app::domain {

    class Lane : public Entity {
    private:
        int lane_id;
        int length;

    public:
        Lane();
        explicit Lane(int lane_id, int length);
        ~Lane() override = default;

        [[nodiscard]] int getId() const override;
        [[nodiscard]] int getLength() const;

        void setLane_id(int lane_id);
        void setLength(int length);

        friend std::ostream &operator<<(std::ostream &os, const Lane &lane);
        friend std::istream &operator>>(std::istream &is, Lane &lane);
    };

}

#endif //LANE_H