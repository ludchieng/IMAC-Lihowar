#include "lihowarlib/AssetManager.hpp"

using namespace lihowar;

namespace lihowar {

AssetManager::AssetManager()
{
    // Import models
    _models.insert(make_pair(ModelID::Cube, new Model(ModelID::Cube)));
    _models.insert(make_pair(ModelID::Platonoid, new Model(ModelID::Platonoid)));
}

}
