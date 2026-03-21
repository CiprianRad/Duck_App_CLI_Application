#include "Repository.h"

namespace ro::ubb::duck_app::repository {

    Repository::Repository(std::shared_ptr<domain::EntityValidator> validator) 
        : validator(std::move(validator)) {}

    std::shared_ptr<domain::Entity> Repository::findById(int id) const {
        auto it = entities.find(id);
        if (it != entities.end()) {
            return it->second;
        }
        return nullptr;
    }

    std::vector<std::shared_ptr<domain::Entity>> Repository::findAll() const {
        std::vector<std::shared_ptr<domain::Entity>> result;
        result.reserve(entities.size());
        for (const auto& [id, entity] : entities) {
            result.push_back(entity);
        }
        return result;
    }

    void Repository::deleteById(int id) {
        if (entities.erase(id) == 0) {
            throw RepositoryException("Entity with this id does not exist!");
        }
    }

    void Repository::save(const std::shared_ptr<domain::Entity> &entity) {
        if (entity == nullptr) return;
        
        validator->validate(*entity);
        
        if (findById(entity->getId())) {
            throw RepositoryException("Entity with this id already exists!");
        }
        entities[entity->getId()] = entity;
    }

    void Repository::update(const std::shared_ptr<domain::Entity> &entity) {
        if (entity == nullptr) return;

        validator->validate(*entity);
        
        if (!findById(entity->getId())) {
            throw RepositoryException("Entity with this id does not exist!");
        }
        entities[entity->getId()] = entity;
    }

}