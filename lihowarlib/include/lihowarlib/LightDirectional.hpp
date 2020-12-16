#ifndef LIHOWAR_LIGHTDIRECTIONAL_HPP
#define LIHOWAR_LIGHTDIRECTIONAL_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/Light.hpp>

namespace lihowar {

class LightDirectional : public Light {

private:
    // MEMBERS
    glm::vec3 _dir;

public:
    // CONSTRUCTORS & DESTRUCTORS
    LightDirectional() = default;
    ~LightDirectional() = default;
    
public:
    // INTERFACE
    glm::vec3 &dir() { return _dir; }
    glm::vec3 dir() const { return _dir; }

};

}


#endif //LIHOWAR_LIGHTDIRECTIONAL