#ifndef VALIDATORS_H
#define VALIDATORS_H
#include <string>
#include "Duck.h"
#include "Lane.h"

namespace ro::ubb::duck_app::domain {

    class DuckAppException : public std::exception {
    private:
        std::string msg;
    public:
        explicit DuckAppException(const std::string& message) : msg(message) {}
        [[nodiscard]] const char* what() const noexcept override { return msg.c_str(); }
    };

    class ValidatorException : public DuckAppException {
    public:
        using DuckAppException::DuckAppException;
    };

    class EntityValidator {
    public:
        virtual ~EntityValidator() = default;
        virtual void validate(const Entity& entity) const = 0;
    };

    class BaseEntityValidator : public EntityValidator {
    public:
        void validate(const Entity& entity) const override {
            int entity_id = entity.getId();
            if (entity_id < 0) {
                throw ValidatorException("Id must be a positive integer! ");
            }
        };
    };

    class DuckValidator : public BaseEntityValidator {
    public:
        void validate(const Entity& entity) const override {
            const Duck* duck = dynamic_cast<const Duck*>(&entity);
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
    };

    class LaneValidator : public BaseEntityValidator {
    public:
        void validate(const Entity& entity) const override {
            const Lane* lane = dynamic_cast<const Lane*>(&entity);
            if (lane == nullptr) {
                throw ValidatorException("Lane must be a lane object");
            }

            BaseEntityValidator::validate(entity);

            if (lane->getLength() <= 0) {
                throw ValidatorException("Length must be greater than zero");
            }
        }
    };

}

#endif //VALIDATORS_H
