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
#ifndef LIHOWAR_LIGHTDIRECTIONAL_HPP
#define LIHOWAR_LIGHTDIRECTIONAL_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Light.hpp>

namespace lihowar {

/**
 * @brief Represents a directional light scene object
 */
class LightDirectional : public Light {

private:
    // MEMBERS

    /**
     * @brief Direction of light emission
     */
    glm::vec3 _dir;

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief Constructor of LightDirectional
     * @param intensity  color intensity of the light
     * @param dir        direction of light emission
     */
    LightDirectional(const glm::vec3 &intensity, const glm::vec3 &dir)
        : Light(intensity), _dir(dir)
    {
        _dir = glm::normalize(_dir);
    }

    /**
     * @brief Destructor of LightDirectional
     */
    ~LightDirectional() override = default;
    
public:
    // INTERFACE

    /**
     * @brief Set the direction of the light object. The vector will be normalized.
     * @param dir  the direction vector (three dimensions)
     */
    void setDir(const glm::vec3 &dir) { _dir = glm::normalize(dir); }
    glm::vec3 dir() const { return _dir; }

};

}


#endif //LIHOWAR_LIGHTDIRECTIONAL