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
#ifndef LIHOWAR_TRACKBALLCAMERA_HPP
#define LIHOWAR_TRACKBALLCAMERA_HPP

#include <functional>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/designpattern/Subject.hpp>
#include <lihowarlib/designpattern/Observer.hpp>
#include <lihowarlib/Object.hpp>
#include <lihowarlib/objects/Player.hpp>
#include <utility>

namespace lihowar {

/**
 * @brief Represents a camera from where the game scene is seen
 *
 * A trackball camera always focuses on a target which has a certain
 * position in the scene.
 */
class TrackballCamera : public dp::Observer {

private:
    // CONSTANTS

    /**
     * @brief Default pitch angle value
     */
    static constexpr float DEFAULT_ANGLE_X = 15.f; //degrees

    /**
     * @brief Default yaw angle value
     */
    static constexpr float DEFAULT_ANGLE_Y = 0.f;  //degrees

    /**
     * @brief Default distance cursor value
     */
    static constexpr float DEFAULT_DISTANCE_CURSOR = .45f;

    /**
     * @brief Minimum value for the distance cursor
     */
    static constexpr float MIN_DISTANCE_CURSOR = 0.f;

    /**
     * @brief Maximum value for the distance cursor
     */
    static constexpr float MAX_DISTANCE_CURSOR = 1.f;

    /**
     * @brief Minimum effective distance between the camera
     * and the target
     */
    static constexpr float MIN_DISTANCE = 1.f;

    /**
     * @brief Maximum effective distance between the camera
     * and the target
     */
    static constexpr float MAX_DISTANCE = 20.f;


    /**
     * @brief Angle factor for position offset
     *
     * Angle factor is the trigonometric tangent of lateral position
     * and effective distance. The higher the factor is, the larger
     * the position offset can be.
     */
    static constexpr float POS_OFFSET_ANGLE_FACTOR = .8f;

    /**
     * @brief Minimum value for position offset on Z axis
     */
    static constexpr float POS_OFFSET_Z_MIN = -5.f;

    /**
     * @brief Maximum value for position offset on Z axis
     */
    static constexpr float POS_OFFSET_Z_MAX = 5.f;

    /**
     * @brief Minimum angle offset value in degrees
     */
    static constexpr float ANG_OFFSET_XY_MIN = -15.f;  //degrees

    /**
     * @brief Maximum angle offset value in degrees
     */
    static constexpr float ANG_OFFSET_XY_MAX = 15.f;   //degrees


    /**
     * @brief Kickback effect due to acceleration coefficient
     */
    static constexpr float POS_OFFSET_KICKBACK_COEF = 10.f;

    /**
     * @brief Coefficient for the angles offset on X axis of the kickback
     * effect due to acceleration
     */
    static constexpr float ANG_OFFSET_X_KICKBACK_COEF = 10.f;   //degrees

    /**
     * @brief Coefficient for the angles offset on Y axis of the kickback
     * effect due to acceleration
     */
    static constexpr float ANG_OFFSET_Y_KICKBACK_COEF = 8000.f; //degrees


    /**
     * @brief Lambda function for basic linear interpolation
     */
    const static std::function<float(float, float, float)> lerp;

    /**
     * @brief Lambda function for quadratic easing
     */
    const static std::function<float(float, float, float, float)> easeQuad;

    /**
     * @brief Lambda function for cosinus easing
     */
    const static std::function<float(float, float, float, float)> easeCos;

private:
    // MEMBERS

    /**
     * @brief Targeted object
     */
    Object &_target;

    /**
     * @brief Value between 0 and 1 which shows the position of the camera
     * on its Z axis
     */
    float _distanceCursor;

    /**
     * @brief Polar coordinates position.
     *
     * Angles between target coordinates basis and
     * effective camera coordinates basis
     */
    glm::vec3 _ang;

    /**
     * @brief Position offset from default camera position
     */
    glm::vec3 _posOffset;

    /**
     * @brief Angles offset from default camera position
     */
    glm::vec3 _angOffset;

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief TrackballCamera class constructor
     * @param target          Targeted object
     * @param distanceCursor  Value between 0 and 1 for Z position of the camera
     * @param ang             Polar coordinate position
     */
    explicit TrackballCamera(
            Object &target,
            float distanceCursor = DEFAULT_DISTANCE_CURSOR,
            glm::vec3 ang = glm::vec3(DEFAULT_ANGLE_X, DEFAULT_ANGLE_Y, 0.));

    /**
     * @brief TrackballCamera class default destructor
     */
    ~TrackballCamera() override = default;
    
public:
    // INTERFACE

    /**
     * @brief Gets the View matrix
     * @return Returns the View matrix
     */
    glm::mat4 getMatView() const;

    /**
     * @brief Gets the field of view in degrees
     * @return Returns the field of view in degrees
     */
    float fov() const { return lerp(cfg::MIN_FOV, cfg::MAX_FOV, _distanceCursor); }

    /**
     * @brief Gets the target position, rotation and scale state
     * @return Returns the target position, rotation and scale state
     */
    Object::PRS &targetPRS() { return _target.prs(); }


    /**
     * @brief Updates state of the camera
     */
    void update() override;

    /**
     * @brief Reset camera position
     */
    void reset();

    /**
     * @brief Updates distance from the target
     * @param delta  Delta distance
     */
    void zoomIn(float delta);

    /**
     * @brief Updates position offset on the camera's Z axis
     * @param delta  Delta distance
     */
    void moveFront(float delta);

    /**
     * @brief Updates position offset on the camera's X axis
     * @param delta  Delta distance
     */
    void moveLeft(float delta);

    /**
     * @brief Updates position offset on the camera's Y axis
     * @param delta  Delta distance
     */
    void moveUp(float delta);

    /**
     * @brief Updates yaw angle position
     * @param degrees  Delta angle in degrees
     */
    void rotateLeft(float degrees);

    /**
     * @brief Updates pitch angle position
     * @param degrees  Delta angle in degrees
     */
    void rotateUp(float degrees);

private:

    /**
     * @brief Computes the effective distance from target
     * @return Returns the effective distance from target
     */
    float distance() const;

    /**
     * @brief Updates position offset to stay in the allowed interval of values
     */
    void updatePosOffset();

    /**
     * @brief Computes the max position offset value for the camera's X axis
     * @return Returns the max position offset value for the camera's X axis
     */
    float maxPosOffsetX() const { return POS_OFFSET_ANGLE_FACTOR * distance(); }

    /**
     * @brief Computes the max position offset value for the camera's Y axis
     * @return Returns the max position offset value for the camera's Y axis
     */
    float maxPosOffsetY() const { return POS_OFFSET_ANGLE_FACTOR * distance(); }

};

}


#endif //LIHOWAR_TRACKBALLCAMERA_HPP
