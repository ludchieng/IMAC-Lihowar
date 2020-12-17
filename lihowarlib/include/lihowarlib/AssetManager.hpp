#ifndef LIHOWAR_ASSETMANAGER_HPP
#define LIHOWAR_ASSETMANAGER_HPP

#include <map>
#include <lihowarlib/common.hpp>
#include <lihowarlib/Mesh.hpp>
#include <lihowarlib/Texture.hpp>

namespace lihowar {

class AssetManager {

private:
    // MEMBERS
    std::map<MeshName, Mesh*> _meshes;
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
    std::map<MeshName, Mesh*> &meshes() { return _meshes; }
    std::map<TextureName, Texture *> textures() { return _textures; }
    GLuint &textureId(TextureName textureName) { return _textures[textureName]->id(); }

private:
    void addMesh(MeshName meshName);
    void addTexture(TextureName texName);
};

}


#endif //LIHOWAR_ASSETMANAGER_HPP
