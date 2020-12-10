#ifndef LIHOWAR_ASSETMANAGER_HPP
#define LIHOWAR_ASSETMANAGER_HPP

#include <map>
#include <lihowarlib/common.hpp>
#include <lihowarlib/Model.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

class AssetManager {

private:
    // MEMBERS
    map<ModelID, Model*> _models;

private:
    // CONSTRUCTORS & DESTRUCTORS
    AssetManager();
    ~AssetManager() = default;
public:
    /// \brief get instance of the AssetManager singleton class
    static AssetManager& instance() {
        static AssetManager instance;
        return instance;
    }
    // prevent instance duplication
    AssetManager(const AssetManager&) = delete;
    AssetManager(AssetManager&&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
    AssetManager& operator=(AssetManager&&) = delete;

public:
    // INTERFACE
    map<ModelID, Model*> &models() { return _models; }
};

}


#endif //LIHOWAR_ASSETMANAGER_HPP
