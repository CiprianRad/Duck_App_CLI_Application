#ifndef DUCK_H
#define DUCK_H

#include <iostream>

namespace ro::ubb::duck_app::domain {

    class Entity {
    public:
        virtual ~Entity() = default;
        [[nodiscard]] virtual int getId() const = 0;
    };

    class Duck : public Entity {
    private:
        int duck_id;
        int speed;
        int resistance;

    public:
        Duck();
        explicit Duck(int duck_id, int speed, int resistance);
        ~Duck() override = default;

        [[nodiscard]] int getId() const override;
        [[nodiscard]] int getSpeed() const;
        [[nodiscard]] int getResistance() const;

        void setDuck_id(int duck_id);
        void setSpeed(int speed);
        void setResistance(int resistance);

        friend std::ostream& operator<<(std::ostream &os, Duck const &duck);
        friend std::istream& operator>>(std::istream &is, Duck &duck);
    };

}

#endif //DUCK_H