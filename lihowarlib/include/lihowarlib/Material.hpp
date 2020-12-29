/*
 *  Copyright (c) 2020-2021 Lihowar
 *
 *  This software is licensed under OSEF License.
 *
 *  The "Software" is defined as the pieces of code, the documentation files, the config
 *  files, the textures assets, the Wavefront OBJ assets, the screenshot image, the sound
 *  effects and music associated with.
 *
 *  This Software is licensed under OSEF License which means IN ACCORDANCE WITH THE LICENSE
 *  OF THE DEPENDENCIES OF THE SOFTWARE, you can use it as you want for any purpose, but
 *  it comes with no guarantee of any kind, provided that you respects the license of the
 *  software dependencies of the piece of code you want to reuse. The dependencies are
 *  listed at the end of the README given in the directory root of the Lihowar repository.
 */
#pragma once
#ifndef LIHOWAR_MATERIAL_HPP
#define LIHOWAR_MATERIAL_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Texture.hpp>

namespace lihowar {

class Material {

private:
    // MEMBERS
    float _kd = .85;
    float _ks = .15;
    float _kl = 1.;
    float _kao = 1.;
    float _kn = 1.;
    float _shininess = 1.;
    GLuint _diffuseTexId;
    GLuint _specularTexId;
    GLuint _luminTexId;
    GLuint _aoTexId;
    GLuint _normalTexId;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Material(
            GLuint diffuseTexId = 0,
            GLuint specularTexId = 0,
            GLuint luminTexId = 0,
            GLuint aoTexId = 0,
            GLuint normalTexId = 0)
       :_diffuseTexId(diffuseTexId),
        _specularTexId(specularTexId),
        _luminTexId(luminTexId),
        _aoTexId(aoTexId),
        _normalTexId(normalTexId)
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
    float kao() const { return _kao; }
    float &kao() { return _kao; }
    float kn() const { return _kn; }
    float &kn() { return _kn; }

    float shininess() const { return _shininess; }
    float &shininess() { return _shininess; }

    GLuint diffuseTexId() const { return _diffuseTexId; }
    GLuint &diffuseTexId() { return _diffuseTexId; }

    GLuint specularTexId() const { return _specularTexId; }
    GLuint &specularTexId() { return _specularTexId; }

    GLuint luminTexId() const { return _luminTexId; }
    GLuint &luminTexId() { return _luminTexId; }

    GLuint aoTexId() const { return _aoTexId; }
    GLuint &aoTexId() { return _aoTexId; }

    GLuint normalTexId() const { return _normalTexId; }
    GLuint &normalTexId() { return _normalTexId; }

    bool hasDiffuseMap() const { return _diffuseTexId != 0; }
    bool hasSpecularMap() const { return _specularTexId != 0; }
    bool hasLuminMap() const { return _luminTexId != 0; }
    bool hasAOMap() const { return _aoTexId != 0; }
    bool hasNormalMap() const { return _normalTexId != 0; }

};

}


#endif //LIHOWAR_MATERIAL_HPP
