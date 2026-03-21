#include "Validators.h"

namespace ro::ubb::duck_app::domain {

    void BaseEntityValidator::validate(const Entity& entity) const {
        if (entity.getId() < 0) {
            throw ValidatorException("Id must be a positive integer!");
        }
    }

    void DuckValidator::validate(const Entity& entity) const {
        const auto* duck = dynamic_cast<const Duck*>(&entity);
        if (duck == nullptr) {
            throw ValidatorException("Duck must be a duck object");
        }

        BaseEntityValidator::validate(entity);

        if (duck->getSpeed() <= 0) {
            throw ValidatorException("Speed must be greater than zero");
        }
        if (duck->getResistance() <= 0) {
            throw ValidatorException("Resistance must be greater than zero");
        }
    }

    void LaneValidator::validate(const Entity& entity) const {
        const auto* lane = dynamic_cast<const Lane*>(&entity);
        if (lane == nullptr) {
            throw ValidatorException("Lane must be a lane object");
        }

        BaseEntityValidator::validate(entity);

        if (lane->getLength() <= 0) {
            throw ValidatorException("Length must be greater than zero");
        }
    }

}