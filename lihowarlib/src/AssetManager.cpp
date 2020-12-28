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
