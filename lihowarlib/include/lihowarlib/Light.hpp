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
#ifndef LIHOWAR_LIGHT_HPP
#define LIHOWAR_LIGHT_HPP

#include <lihowarlib/GameConfig.hpp>

namespace lihowar {

/**
 * @brief Represents a light in a game scene
 */
class Light {

protected:
    // MEMBERS

    /**
     * @brief Color intensity
     *
     * Should be three float values corresponding to
     * the red, green and blue amplitude of the light.
     * These values can exceed 1.0
     */
    glm::vec3 _intensity;

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief Light class constructor
     * @param intensity  Color intensity of the light
     */
    explicit Light(const glm::vec3 &intensity)
        : _intensity(intensity)
    {}

    /**
     * @brief Light class destructor
     */
    virtual ~Light() = default;
    
public:
    // INTERFACE

    /**
     * Gets the intensity of the light
     * @return Returns the intensity of the light
     */
    glm::vec3 &intensity() { return _intensity; }
    glm::vec3 intensity() const { return _intensity; }

};

}


#endif //LIHOWAR_LIGHT_HPP
