#ifndef LIHOWAR_ASSETMANAGER_HPP
#define LIHOWAR_ASSETMANAGER_HPP

#include <map>
#include <lihowarlib/common.hpp>
#include <lihowarlib/Model.hpp>
#include <lihowarlib/Texture.hpp>

namespace lihowar {

class AssetManager {

private:
    // MEMBERS
    std::map<ModelName, Model*> _models;
    std::map<TextureName, Texture*> _textures;

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
    std::map<ModelName, Model*> &models() { return _models; }
    std::map<TextureName, Texture *> textures() { return _textures; }
    GLuint &textureId(TextureName textureName) { return _textures[textureName]->id(); }

private:
    void addModel(ModelName modelName);
    void addTexture(TextureName texName);
};

}


#endif //LIHOWAR_ASSETMANAGER_HPP
