#ifndef LIHOWAR_LIGHT_HPP
#define LIHOWAR_LIGHT_HPP

#include <lihowarlib/GameConfig.hpp>

namespace lihowar {

class Light {
    friend class SceneSerializer;

protected:
    // MEMBERS
    glm::vec3 _intensity;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Light(const glm::vec3 &intensity)
        : _intensity(intensity)
    {}

    virtual ~Light() = default;
    
public:
    // INTERFACE
    glm::vec3 &intensity() { return _intensity; }
    glm::vec3 intensity() const { return _intensity; }

};

}


#endif //LIHOWAR_LIGHT_HPP
