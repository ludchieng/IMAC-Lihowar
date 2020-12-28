#ifndef LIHOWAR_PLATEFORM_HPP
#define LIHOWAR_PLATEFORM_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Object.hpp>

namespace lihowar {

class Plateform : public Object {

private:
    // MEMBERS

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Plateform(PRS prs = PRS())
       :Object(
            *AssetManager::meshes()[MeshName::PLATEFORM],
            *new Material(
                    AssetManager::texId(TextureName::PLATEFORM_DIFF),
                    AssetManager::NO_TEXTURE,
                    AssetManager::NO_TEXTURE,
                    AssetManager::texId(TextureName::PLATEFORM_AO),
                    AssetManager::texId(TextureName::PLATEFORM_NORMAL)),
            prs)
    {}
    
public:
    // INTERFACE

};

}


#endif //LIHOWAR_PLATEFORM_HPP
