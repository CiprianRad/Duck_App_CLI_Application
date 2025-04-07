//
// Created by cipri on 4/4/2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

#include "../domain/validators.h"


namespace ro::ubb::duck_app::repository {
    class RepositoryException : public domain::DuckAppException {
    public:
        using DuckAppException::DuckAppException;
    };

    class Repository {
    private:
        std::unordered_map<int, std::shared_ptr<domain::Entity>> entities;
        std::shared_ptr<domain::EntityValidator> validator;
    public:
        explicit Repository(std::shared_ptr<domain::EntityValidator> validator) : validator(validator) {}
        virtual ~Repository() = default;

        std::shared_ptr<domain::Entity> findById(int id) const {
            auto it = entities.find(id);
            if (it != entities.end()) {
                return it->second;
            }
            return nullptr;
        }

        std::vector<std::shared_ptr<domain::Entity>> findAll() const {
            std::vector<std::shared_ptr<domain::Entity>> result;
            for (const auto& [id, entity]: this->entities) {
                result.emplace_back(entity);
            }
            return result;
        }

        void deleteById(int id) {
            if (!findById(id)) {
                throw RepositoryException("Entity with this id does not exist! ");
            }
            entities.erase(id);
        }

        virtual void save(const std::shared_ptr<domain::Entity> &entity) {
            validator->validate(*entity);
            if (findById(entity->getId())) {
                throw RepositoryException("Entity with this id already exists! ");
            }
            entities[entity->getId()] = entity;
        }

        void update(const std::shared_ptr<domain::Entity> &entity) {
            validator ->validate(*entity);
            if (!findById(entity->getId())) {
                throw RepositoryException("Entity with this id does not exist! ");
            }
            entities[entity->getId()] = entity;
        }
    };

    //TODO: Override the what() function in all the RepositoryException class. Try to make it case dependent
    //TODO: Override the what() function in all the other Exception classes. Make them case dependent
}

#endif //REPOSITORY_H
