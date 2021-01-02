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

/**
 * @brief Represents a material of a game object
 */
class Material {

private:
    // MEMBERS

    /**
     * @brief Diffuse coefficient
     */
    float _kd = .85;

    /**
     * @brief Specular coefficient
     */
    float _ks = .15;

    /**
     * @brief Luminance coefficient
     */
    float _kl = 1.;

    /**
     * @brief Ambient occlusion coefficient
     */
    float _kao = 1.;

    /**
     * @brief Normal coefficient
     */
    float _kn = 1.;

    /**
     * @brief Shininess coefficient for blinn-phong illumination
     */
    float _shininess = 1.;

    /**
     * @brief Diffuse texture GL ID
     */
    GLuint _diffuseTexId;

    /**
     * @brief Specular texture GL ID
     */
    GLuint _specularTexId;

    /**
     * @brief Luminance texture GL ID
     */
    GLuint _luminTexId;

    /**
     * @brief Ambient occlusion texture GL ID
     */
    GLuint _aoTexId;

    /**
     * @brief Normal texture GL ID
     */
    GLuint _normalTexId;

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief Material class constructor
     * @param diffuseTexId   Diffuse texture GL ID
     * @param specularTexId  Specular texture GL ID
     * @param luminTexId     Luminance texture GL ID
     * @param aoTexId        Ambient occlusion texture GL ID
     * @param normalTexId    Normal texture GL ID
     */
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

    /**
     * @brief Material class destructor
     */
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
