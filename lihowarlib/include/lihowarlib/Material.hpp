#ifndef LIHOWAR_MATERIAL_HPP
#define LIHOWAR_MATERIAL_HPP

#include <lihowarlib/common.hpp>

namespace lihowar {

class Material {

private:
    // MEMBERS
    float _kd;
    float _ks;
    float _shininess;
    GLuint _textureId;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Material(
        float kd = .85, float ks = .15,
        float shininess = 1., GLuint textureId = 0)
       :_kd(kd), _ks(ks),
        _shininess(shininess), _textureId(textureId)
    {}

    explicit Material(GLuint textureId)
       :_kd(.85), _ks(.15),
        _shininess(1.), _textureId(textureId)
    {}

    ~Material() = default;

public:
    // INTERFACE
    float &kd() { return _kd; }
    float &ks() { return _ks; }
    float &shininess() { return _shininess; }
    GLuint &textureId() { return _textureId; }
    float kd() const { return _kd; }
    float ks() const { return _ks; }
    float shininess() const { return _shininess; }
    GLuint textureId() const { return _textureId; }

    bool hasTexture() const { return _textureId != 0; }

};

}


#endif //LIHOWAR_MATERIAL_HPP
