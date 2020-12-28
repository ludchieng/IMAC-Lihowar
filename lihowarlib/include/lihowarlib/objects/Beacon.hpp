#ifndef LIHOWAR_BEACON_HPP
#define LIHOWAR_BEACON_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Object.hpp>

namespace lihowar {

class Beacon : public Object {

private:
    // MEMBERS

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Beacon(
            MeshName meshName,
            Material &material,
            PRS prs = PRS())
       :Object(
            *AssetManager::meshes()[meshName],
            material,
            prs)
    {}
    
public:
    // INTERFACE

};

}


#endif //LIHOWAR_BEACON_HPP
