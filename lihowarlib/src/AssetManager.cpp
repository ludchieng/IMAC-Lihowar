#include "lihowarlib/AssetManager.hpp"

using namespace std;
using namespace lihowar;

namespace lihowar {

AssetManager::AssetManager()
{
    // Import meshes
    for (int i = (int) MeshName::first; i <= (int) MeshName::last; ++i)
        addMesh( static_cast<MeshName>(i) );

    // Import textures
    for (int i = (int) TextureName::first; i <= (int) TextureName::last; ++i)
        addTexture( static_cast<TextureName>(i) );
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
