#ifndef LIHOWAR_ISLAND_HPP
#define LIHOWAR_ISLAND_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Object.hpp>

namespace lihowar {

class Island : public Object {

private:
    // MEMBERS

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Island(
            MeshName meshName,
            PRS prs = PRS())
       :Object(
            *AssetManager::mesh(meshName),
            AssetManager::NO_TEXTURE,
            prs)
    {}
    
public:
    // INTERFACE

};

}


#endif //LIHOWAR_ISLAND_HPP
