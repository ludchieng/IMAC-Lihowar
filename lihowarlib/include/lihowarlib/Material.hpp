#ifndef LIHOWAR_MATERIAL_HPP
#define LIHOWAR_MATERIAL_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/Texture.hpp>

namespace lihowar {

class Material {

private:
    // MEMBERS
    float _kd;
    float _ks;
    float _kl;
    float _shininess;
    GLuint _diffuseTexId;
    GLuint _specularTexId;
    GLuint _luminTexId;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Material(
            GLuint diffuseTexId = 0,
            GLuint specularTexId = 0,
            GLuint luminTexId = 0)
       :_kd(.85), _ks(.15), _kl(1.), _shininess(1.),
        _diffuseTexId(diffuseTexId),
        _specularTexId(specularTexId),
        _luminTexId(luminTexId)
    {}

    ~Material() = default;

public:
    // INTERFACE
    float kd() const { return _kd; }
    float &kd() { return _kd; }
    float ks() const { return _ks; }
    float &ks() { return _ks; }
    float kl() const { return _kl; }
    float &kl() { return _kl; }

    float shininess() const { return _shininess; }
    float &shininess() { return _shininess; }

    GLuint diffuseTexId() const { return _diffuseTexId; }
    GLuint &diffuseTexId() { return _diffuseTexId; }

    GLuint specularTexId() const { return _specularTexId; }
    GLuint &specularTexId() { return _specularTexId; }

    GLuint luminTexId() const { return _luminTexId; }
    GLuint &luminTexId() { return _luminTexId; }

    bool hasDiffuseMap() const { return _diffuseTexId != 0; }
    bool hasSpecularMap() const { return _specularTexId != 0; }
    bool hasLuminMap() const { return _luminTexId != 0; }

};

}


#endif //LIHOWAR_MATERIAL_HPP
