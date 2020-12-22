#ifndef LIHOWAR_PLAYER_HPP
#define LIHOWAR_PLAYER_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/ObjectDynamic.hpp>
#include <lihowarlib/AssetManager.hpp>

namespace lihowar {

class Player : public ObjectDynamic {
    friend class SceneSerializer;

protected:
    // MEMBERS

public:
    // CONSTRUCTORS & DESTRUCTORS
    Player()
       :ObjectDynamic(
          *AssetManager::instance().meshes()[MeshName::BALLOON] )
    {
        _prs.rot() = glm::vec3(0., 0., 5.);
        _angVel = glm::vec3(0., .001, 0.);
    }
    
public:
    // INTERFACE


};

}


#endif //LIHOWAR_PLAYER_HPP
