#include "lihowarlib/AssetManager.hpp"

using namespace std;
using namespace lihowar;

namespace lihowar {

AssetManager::AssetManager()
{
    // Import meshes
    for (int i = MESHNAME_FIRST; i <= MESHNAME_LAST; ++i)
        addMesh( static_cast<MeshName>(i) );

    // Import textures
    for (int i = TEXTURENAME_FIRST; i <= TEXTURENAME_LAST; ++i)
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
