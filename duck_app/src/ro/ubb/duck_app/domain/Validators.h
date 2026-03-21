#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <string>
#include <exception>
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
        void validate(const Entity& entity) const override;
    };

    class DuckValidator : public BaseEntityValidator {
    public:
        void validate(const Entity& entity) const override;
    };

    class LaneValidator : public BaseEntityValidator {
    public:
        void validate(const Entity& entity) const override;
    };

}

#endif //VALIDATORS_H