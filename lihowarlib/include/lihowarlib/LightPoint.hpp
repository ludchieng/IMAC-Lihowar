#ifndef LIHOWAR_LIGHTPOINT_HPP
#define LIHOWAR_LIGHTPOINT_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/Light.hpp>
#include <lihowarlib/Object.hpp>

namespace lihowar {

class LightPoint : public Light {

private:
    // MEMBERS
    glm::vec3 &_posParent;
    glm::vec3 _posOffset;

public:
    // CONSTRUCTORS & DESTRUCTORS
    LightPoint(
            const glm::vec3 &intensity,
            glm::vec3 &posParent,
            const glm::vec3 &posOffset = glm::vec3(0., 0., 0.))
        : Light(intensity), _posParent(posParent), _posOffset(posOffset)
    {}
    ~LightPoint() override = default;

public:
    // INTERFACE
    glm::vec3 &posParent() { return _posParent; }
    glm::vec3 &posOffset() { return _posOffset; }
    glm::vec3 posParent() const { return _posParent; }
    glm::vec3 posOffset() const { return _posOffset; }
    glm::vec3 pos() const { return _posParent + _posOffset; }

};

}


#endif //LIHOWAR_LIGHTPOINT_HPP
