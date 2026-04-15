#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "../domain/Validators.h"

namespace ro::ubb::duck_app::repository {

    class RepositoryException : public ro::ubb::duck_app::domain::DuckAppException {
    public:
        using DuckAppException::DuckAppException;
        // The TODO for what() can be handled here or in the .cpp
    };

    class Repository {
    private:
        std::unordered_map<int, std::shared_ptr<ro::ubb::duck_app::domain::Entity>> entities;
        std::shared_ptr<ro::ubb::duck_app::domain::EntityValidator> validator;

    public:
        explicit Repository(std::shared_ptr<ro::ubb::duck_app::domain::EntityValidator> validator);
        virtual ~Repository() = default;

        [[nodiscard]] std::shared_ptr<ro::ubb::duck_app::domain::Entity> findById(int id) const;
        [[nodiscard]] std::vector<std::shared_ptr<ro::ubb::duck_app::domain::Entity>> findAll() const;

        virtual void deleteById(int id);
        virtual void save(const std::shared_ptr<ro::ubb::duck_app::domain::Entity> &entity);
        virtual void update(const std::shared_ptr<ro::ubb::duck_app::domain::Entity> &entity);
    };

    //TODO: Override the what() function in all the RepositoryException class. Try to make it case dependent
    //TODO: Override the what() function in all the other Exception classes. Make them case dependent
}

#endif //REPOSITORY_H