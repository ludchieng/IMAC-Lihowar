#include "lihowarlib/AssetManager.hpp"

using namespace std;
using namespace lihowar;

namespace lihowar {

AssetManager::AssetManager()
{
    // Import models
    for (int i = MODELNAME_FIRST; i <= MODELNAME_LAST; ++i)
        addModel( static_cast<ModelName>(i) );

    // Import textures
    for (int i = TEXTURENAME_FIRST; i <= TEXTURENAME_LAST; ++i)
        addTexture( static_cast<TextureName>(i) );
}


void AssetManager::addModel(ModelName modelName)
{
    _models.insert( make_pair(modelName,new Model(modelName)) );
}


void AssetManager::addTexture(TextureName texName)
{
    _textures.insert( make_pair(texName,new Texture(texName)) );
}

}
