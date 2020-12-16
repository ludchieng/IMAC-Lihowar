#ifndef LIHOWAR_LIGHT_HPP
#define LIHOWAR_LIGHT_HPP

#include <lihowarlib/common.hpp>

namespace lihowar {

class Light {
    friend class SceneSerializer;

private:
    // MEMBERS
    float _intensity;

public:
    // CONSTRUCTORS & DESTRUCTORS
    Light() = default;
    ~Light() = default;
    
public:
    // INTERFACE
    float &intensity() { return _intensity; }
    float intensity() const { return _intensity; }

};

}


#endif //LIHOWAR_LIGHT_HPP
