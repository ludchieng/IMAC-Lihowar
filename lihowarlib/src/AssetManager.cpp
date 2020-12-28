#include "lihowarlib/AssetManager.hpp"
#include <cassert>

using namespace std;
using namespace lihowar;

namespace lihowar {

AssetManager::AssetManager()
{
    // Import meshes
    unsigned int count = 0;
    for (int i = (int) MeshName::first; i <= (int) MeshName::last; ++i) {
        addMesh( static_cast<MeshName>(i) );
        ++count;
    }

    assert(count == Mesh::PATHS.size() && "MeshName enum elements count does not match with Mesh PATHS size. Maybe you forgot to update 'MeshName::last'?");

    // Import textures
    count = 0;
    for (int i = (int) TextureName::first; i <= (int) TextureName::last; ++i) {
        addTexture( static_cast<TextureName>(i) );
        ++ count;
    }

    assert(count == Texture::PATHS.size() && "TextureName enum elements count does not match with Texture PATHS size. Maybe you forgot to update 'TextureName::last'?");
}


void AssetManager::addMesh(MeshName meshName)
{
    _meshes.insert( make_pair(meshName,new Mesh(meshName)) );
}


void AssetManager::addTexture(TextureName texName)
{
    _textures.insert( make_pair(texName,new Texture(texName)) );
}

}
