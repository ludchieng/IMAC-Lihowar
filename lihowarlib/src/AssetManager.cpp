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
#include "lihowarlib/AssetManager.hpp"
#include <cassert>
#include <memory>

using namespace std;
using namespace lihowar;

namespace lihowar {

AssetManager::AssetManager()
{
    if (!checkAssets())
        cerr << "[AssetManager::AssetManager] MeshName or TextureName enums does not match with PATHS map";
}


Mesh *AssetManager::mesh(MeshName meshName)
{
    auto pair = meshes().find(meshName);
    if (pair == meshes().end())
        return addMesh(meshName);
    return pair->second;
}


Texture *AssetManager::tex(TextureName textureName)
{
    auto pair = textures().find(textureName);
    if (pair == textures().end())
        return addTexture(textureName);
    return pair->second;
}


Mesh *AssetManager::addMesh(MeshName meshName)
{
    auto pair = std::make_pair(meshName, new Mesh(meshName));
    meshes().insert(pair);
    return pair.second;
}

Texture *AssetManager::addTexture(TextureName texName)
{
    auto pair = std::make_pair(texName, new Texture(texName));
    textures().insert(pair);
    return pair.second;
}


bool AssetManager::checkAssets()
{
    // Check meshes count
    unsigned int count = 0;
    for (int i = (int) MeshName::first; i <= (int) MeshName::last; ++i)
        ++count;

    // for dev
    assert(count == Mesh::PATHS.size() && "MeshName enum elements count does not match with Mesh PATHS size. Maybe you forgot to update 'MeshName::last'?");

    if (count != Mesh::PATHS.size())
        return false;

        // Check textures count
    count = 0;
    for (int i = (int) TextureName::first; i <= (int) TextureName::last; ++i)
        ++ count;

    // for dev
    assert(count == Texture::PATHS.size() && "TextureName enum elements count does not match with Texture PATHS size. Maybe you forgot to update 'TextureName::last'?");

    if (count != Texture::PATHS.size())
        return false;

    return true;
}

}
