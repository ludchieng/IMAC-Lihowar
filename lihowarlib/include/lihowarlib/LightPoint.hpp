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
#ifndef LIHOWAR_LIGHTPOINT_HPP
#define LIHOWAR_LIGHTPOINT_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Light.hpp>
#include <lihowarlib/Object.hpp>

namespace lihowar {

/**
 * @brief Represents a point light in a game scene
 */
class LightPoint : public Light {

private:
    // MEMBERS

    /**
     * @brief Position of the potential parent
     */
    glm::vec3 &_posParent;

    /**
     * @brief Position offset from the anchor point of the parent object
     */
    glm::vec3 _posOffset;

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief LightPoint class constructor
     * @param intensity  Color intensity of the light
     * @param posParent  Position of the potential parent
     * @param posOffset  Position offset from the anchor point of the parent object
     */
    LightPoint(
            const glm::vec3 &intensity,
            glm::vec3 &posParent,
            const glm::vec3 &posOffset = glm::vec3(0., 0., 0.))
        : Light(intensity), _posParent(posParent), _posOffset(posOffset)
    {}

    /**
     * @brief LightPoint class destructor
     */
    ~LightPoint() override = default;

public:
    // INTERFACE

    /**
     * @brief Gets the position of the potential parent
     * @return the position of the potential parent
     */
    glm::vec3 &posParent() { return _posParent; }
    glm::vec3 posParent() const { return _posParent; }

    /**
     * @brief Gets the offset position
     * @return Returns the offset position
     */
    glm::vec3 &posOffset() { return _posOffset; }
    glm::vec3 posOffset() const { return _posOffset; }

    /**
     * @brief Gets the position
     * @return the position
     */
    glm::vec3 pos() const { return _posParent + _posOffset; }

};

}


#endif //LIHOWAR_LIGHTPOINT_HPP
