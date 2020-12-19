#ifndef LIHOWAR_PLAYER_HPP
#define LIHOWAR_PLAYER_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/Object.hpp>
#include <lihowarlib/AssetManager.hpp>

namespace lihowar {

class Player : public Object {
    friend class SceneSerializer;

protected:
    // MEMBERS

public:
    // CONSTRUCTORS & DESTRUCTORS
    Player()
       :Object(
          *AssetManager::instance().meshes()[MeshName::BALLOON] )
    {}
    
public:
    // INTERFACE


};

}


#endif //LIHOWAR_PLAYER_HPP
