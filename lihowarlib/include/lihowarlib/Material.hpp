#ifndef LIHOWAR_MATERIAL_HPP
#define LIHOWAR_MATERIAL_HPP

#include <lihowarlib/common.hpp>

namespace lihowar {

class Material {

private:
    // MEMBERS
    float _kd;
    float _ks;
    float _ka;
    float _shininess;
    GLuint _textureId;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Material(
        float kd = .35, float ks = .85, float ka = .05,
        float shininess = 2., GLuint textureId = 0)
       :_kd(kd), _ks(ks), _ka(ka),
        _shininess(shininess), _textureId(textureId)
    {}

    explicit Material(GLuint textureId)
       :_kd(.35), _ks(.85), _ka(.05),
        _shininess(2.), _textureId(textureId)
    {}

    ~Material() = default;

public:
    // INTERFACE
    float &kd() { return _kd; }
    float &ks() { return _ks; }
    float &ka() { return _ka; }
    float &shininess() { return _shininess; }
    GLuint &textureId() { return _textureId; }
    float kd() const { return _kd; }
    float ks() const { return _ks; }
    float ka() const { return _ka; }
    float shininess() const { return _shininess; }
    GLuint textureId() const { return _textureId; }

    bool hasTexture() const { return _textureId != 0; }

};

}


#endif //LIHOWAR_MATERIAL_HPP
