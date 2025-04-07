#ifndef DUCK_H
#define DUCK_H

#include<iostream>
namespace ro::ubb::duck_app::domain {
    class Entity {
    public:
        virtual ~Entity() = default;
        [[nodiscard]] virtual int getId() const = 0;
    };

    class Duck : public Entity{
    private:
        int duck_id;
        int speed;
        int resistance;
    public:
        Duck() {this->duck_id = 0; this->speed = 0; this->resistance = 0;}
        explicit Duck(int duck_id, int speed, int resistance) : duck_id(duck_id), speed(speed), resistance(resistance) {};
        ~Duck() override = default;
        [[nodiscard]] int getId() const override {return duck_id;}
        [[nodiscard]] int getSpeed() const {return speed;}
        [[nodiscard]] int getResistance() const {return resistance;}
        void setDuck_id(int duck_id) {this->duck_id = duck_id;} // <=> void setDuck_id(int duck_id) {duck_id_=duck_id}
        void setSpeed(int speed) {this->speed = speed;}
        void setResistance(int resistance) {this->resistance = resistance;}
        friend std::ostream& operator<<(std::ostream &os, Duck const &duck) {os << "Duck ID: " << duck.getId() << " Speed: " << duck.getSpeed() << " Resistance: " << duck.getResistance()<<std::endl; return os;}
        friend std::istream& operator>>(std::istream &is, Duck &duck) {int duck_id; std::cout << "Duck ID = "; is >> duck_id; duck.setDuck_id(duck_id); int speed; std::cout << "Duck Speed: "; is >> speed; duck.setSpeed(speed); int resistance; std::cout << "Duck Resistance: "; is >> resistance; duck.setResistance(resistance); return is;}
    };
}

#endif //DUCK_H
