#ifndef LIHOWAR_PENTABALL_HPP
#define LIHOWAR_PENTABALL_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Object.hpp>

namespace lihowar {

class Pentaball : public Object {

private:
    // MEMBERS

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Pentaball(PRS prs = PRS())
       :Object(
            *AssetManager::meshes()[MeshName::PENTABALL],
            *new Material(
                    AssetManager::texId(TextureName::PENTABALL_DIFF),
                    AssetManager::texId(TextureName::PENTABALL_SPEC),
                    AssetManager::texId(TextureName::PENTABALL_LUMIN),
                    AssetManager::texId(TextureName::PENTABALL_AO),
                    AssetManager::texId(TextureName::PENTABALL_NORMAL)),
            prs)
    {}
    
public:
    // INTERFACE

};

}


#endif //LIHOWAR_PENTABALL_HPP
