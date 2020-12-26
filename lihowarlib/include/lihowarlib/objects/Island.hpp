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
        Mesh& mesh,
        GLuint textureId = 0,
        PRS prs = PRS())
       :Object(mesh, textureId, prs)
    {}
    
public:
    // INTERFACE

};

}


#endif //LIHOWAR_ISLAND_HPP
