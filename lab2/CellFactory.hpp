#pragma once

#include <map>
#include <memory>
#include <functional>

template <typename AbstractProduct, typename IdentifierType>
class CellFactory
{
public: 
    using CreatorFn = std::function<std::unique_ptr<AbstractProduct>()>;
    bool Register(const IdentifierType& id, CreatorFn creator)
    {
        return creators_.emplace(id, creator).second;
    }

    std::unique_ptr<AbstractProduct> Create(const IdentifierType& id) const
    {
        auto it = creators_.find(id);
        if (it != creators_.end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    std::map<IdentifierType, CreatorFn> creators_;
};
