#ifndef LIHOWAR_LIGHTDIRECTIONAL_HPP
#define LIHOWAR_LIGHTDIRECTIONAL_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Light.hpp>

namespace lihowar {

class LightDirectional : public Light {

private:
    // MEMBERS
    glm::vec3 _dir;

public:
    // CONSTRUCTORS & DESTRUCTORS
    LightDirectional(const glm::vec3 &intensity, const glm::vec3 &dir)
        : Light(intensity), _dir(dir)
    {
        _dir = glm::normalize(_dir);
    }
    ~LightDirectional() override = default;
    
public:
    // INTERFACE
    void setDir(const glm::vec3 &dir) { _dir = glm::normalize(dir); }
    glm::vec3 dir() const { return _dir; }

};

}


#endif //LIHOWAR_LIGHTDIRECTIONAL