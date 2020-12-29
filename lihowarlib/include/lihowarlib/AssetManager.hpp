/*
 *  Copyright (c) 2020-2021 Lihowar
 *
 *  This software is licensed under OSEF License.
 *
 *  The "Software" is defined as the pieces of code, the documentation files, the config
 *  files, the textures assets, the Wavefront OBJ assets, the screenshot image, the sound
 *  effects and music associated with.
 *
 *  This Software is licensed under OSEF License which means IN ACCORDANCE WITH THE LICENSE
 *  OF THE DEPENDENCIES OF THE SOFTWARE, you can use it as you want for any purpose, but
 *  it comes with no guarantee of any kind, provided that you respects the license of the
 *  software dependencies of the piece of code you want to reuse. The dependencies are
 *  listed at the end of the README given in the directory root of the Lihowar repository.
 */
#pragma once
#ifndef LIHOWAR_ASSETMANAGER_HPP
#define LIHOWAR_ASSETMANAGER_HPP

#include <map>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Mesh.hpp>
#include <lihowarlib/Texture.hpp>

namespace lihowar {

class AssetManager {

public:
    // CONSTANTS
    static const int NO_TEXTURE = 0;

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
    static std::map<MeshName, Mesh*> &meshes() { return instance()._meshes; }
    static std::map<TextureName, Texture*> &textures() { return instance()._textures; }

    static Mesh* mesh(MeshName meshName);
    static Texture* tex(TextureName textureName);

    static GLuint &texId(TextureName textureName) { return tex(textureName)->id(); }

private:
    static Mesh* addMesh(MeshName meshName);
    static Texture* addTexture(TextureName texName);

    static bool hasMesh(MeshName meshName) { return meshes().find(meshName) != meshes().end(); }
    static bool hasTexture(TextureName texName) { return textures().find(texName) != textures().end(); }

    static bool checkAssets();
};

}


#endif //LIHOWAR_ASSETMANAGER_HPP
