#include "Duck.h"

namespace ro::ubb::duck_app::domain {

    Duck::Duck() : duck_id(0), speed(0), resistance(0) {}

    Duck::Duck(int duck_id, int speed, int resistance) 
        : duck_id(duck_id), speed(speed), resistance(resistance) {}

    int Duck::getId() const {
        return duck_id;
    }

    int Duck::getSpeed() const {
        return speed;
    }

    int Duck::getResistance() const {
        return resistance;
    }

    void Duck::setDuck_id(int duck_id) {
        this->duck_id = duck_id;
    }

    void Duck::setSpeed(int speed) {
        this->speed = speed;
    }

    void Duck::setResistance(int resistance) {
        this->resistance = resistance;
    }

    std::ostream& operator<<(std::ostream &os, Duck const &duck) {
        os << "Duck ID: " << duck.duck_id 
           << " Speed: " << duck.speed 
           << " Resistance: " << duck.resistance << std::endl;
        return os;
    }

    std::istream& operator>>(std::istream &is, Duck &duck) {
        std::cout << "Duck ID = ";
        is >> duck.duck_id;
        std::cout << "Duck Speed: ";
        is >> duck.speed;
        std::cout << "Duck Resistance: ";
        is >> duck.resistance;
        return is;
    }

}