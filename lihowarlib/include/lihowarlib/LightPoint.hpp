#ifndef LIHOWAR_LIGHTPOINT_HPP
#define LIHOWAR_LIGHTPOINT_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/Light.hpp>

namespace lihowar {

class LightPoint : public Light {

private:
    // MEMBERS
    glm::vec3 _pos;

public:
    // CONSTRUCTORS & DESTRUCTORS
    LightPoint() = default;
    ~LightPoint() = default;

public:
    // INTERFACE
    glm::vec3 &pos() { return _pos; }
    glm::vec3 pos() const { return _pos; }

};

}


#endif //LIHOWAR_LIGHTPOINT_HPP
