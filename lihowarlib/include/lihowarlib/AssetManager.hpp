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

/**
 * @brief Singleton class to set up and access textures and 3D meshes
 */
class AssetManager {

public:
    // CONSTANTS

    /**
     * @brief GL ID constant corresponding to the null texture
     */
    static const int NO_TEXTURE = 0;

private:
    // MEMBERS

    /**
     * @brief Map of meshes indexed with a MeshName.
     * The meshes map indexes meshes that are loaded in memory
     */
    std::map<MeshName, Mesh*> _meshes;

    /**
     * @brief Map of textures indexed with a TextureName.
     * The textures map indexes textures that are loaded in memory
     */
    std::map<TextureName, Texture*> _textures;

private: // singleton
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief AssetManager class default constructor
     */
    AssetManager();

    /**
     * @brief AssetManager class default destructor
     */
    ~AssetManager() = default;

public:
    /**
     * @brief Gets instance of the AssetManager singleton class
     */
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

    /**
     * @brief Gets the meshes map
     * @return Returns the meshes map
     */
    static std::map<MeshName, Mesh*> &meshes() { return instance()._meshes; }

    /**
     * @brief Gets the textures map
     * @return Returns the textures map
     */
    static std::map<TextureName, Texture*> &textures() { return instance()._textures; }


    /**
     * @brief Gets the requested mesh
     * @param meshName  MeshName of the requested mesh
     * @return Returns the pointer of the requested mesh
     */
    static Mesh* mesh(MeshName meshName);

    /**
     * @brief Gets the requested texture
     * @param textureName  TextureName of the requested texture
     * @return Returns the pointer of the requested texture
     */
    static Texture* tex(TextureName textureName);

    /**
     * @brief Gets texture GL ID from its corresponding TextureName
     * @param textureName  TextureName of the requested texture ID
     * @return Returns the texture GL ID of the requested texture
     */
    static GLuint &texId(TextureName textureName) { return tex(textureName)->id(); }

private:

    /**
     * @brief Add a mesh to the meshes map
     * @param meshName  mesh to add
     * @return Returns the requested mesh
     */
    static Mesh* addMesh(MeshName meshName);

    /**
     * @brief Add a texture to the textures map
     * @param texName  MeshName
     * @return Returns the requested texture
     */
    static Texture* addTexture(TextureName texName);


    /**
     * @brief Returns true if the given mesh name corresponds to a mesh already
     * loaded in the meshes map, false otherwise
     * @param meshName  Requested mesh name
     * @return Returns true if the given mesh name corresponds to a mesh already
     * loaded in the meshes map, false otherwise
     */
    static bool hasMesh(MeshName meshName) { return meshes().find(meshName) != meshes().end(); }

    /**
     * @brief Returns true if the given texture name corresponds to a texture already
     * loaded in the textures map, false otherwise
     * @param texName  Requested texture name
     * @return Returns true if the given texture name corresponds to a texture already
     * loaded in the textures map, false otherwise
     */
    static bool hasTexture(TextureName texName) { return textures().find(texName) != textures().end(); }

    /**
     * @brief Assert that hardcoded assets names, file paths are coherent
     * @return Returns true if no incoherence have been detected in the assets names or file paths, false otherwise
     */
    static bool checkAssets();
};

}


#endif //LIHOWAR_ASSETMANAGER_HPP
