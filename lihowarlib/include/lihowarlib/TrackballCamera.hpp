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

class TrackballCamera : public dp::Observer {

private:
    // CONSTANTS
    static constexpr float DEFAULT_DISTANCE_CURSOR = .45f;
    static constexpr float DEFAULT_ANGLE_X = 15.f; //degrees
    static constexpr float DEFAULT_ANGLE_Y = 0.f; //degrees
    static constexpr float MIN_DISTANCE_CURSOR = 0.f;
    static constexpr float MAX_DISTANCE_CURSOR = 1.f;
    static constexpr float MIN_DISTANCE = 1.f;
    static constexpr float MAX_DISTANCE = 20.f;
    static constexpr float POS_OFFSET_ANGLE_FACTOR = .8f;
    static constexpr float POS_OFFSET_Z_MIN = -5.f;
    static constexpr float POS_OFFSET_Z_MAX = 5.f;
    static constexpr float POS_OFFSET_Z_COEF = 10.f;
    static constexpr float ANG_OFFSET_XY_MIN = -15.f;
    static constexpr float ANG_OFFSET_XY_MAX = 15.f;
    static constexpr float ANG_OFFSET_X_COEF = 10.f;
    static constexpr float ANG_OFFSET_Y_COEF = 8000.f;
    const static std::function<float(float, float, float)> lerp;
    const static std::function<float(float, float, float, float)> easeQuad;
    const static std::function<float(float, float, float, float)> easeCos;

private:
    // MEMBERS
    Object &_target;
    float _distanceCursor;
    glm::vec3 _ang;
    glm::vec3 _posOffset;
    glm::vec3 _angOffset;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit TrackballCamera(
            Object &target,
            float distanceCursor = DEFAULT_DISTANCE_CURSOR,
            glm::vec3 ang = glm::vec3(DEFAULT_ANGLE_X, DEFAULT_ANGLE_Y, 0.));

    ~TrackballCamera() override = default;
    
public:
    // INTERFACE
    glm::mat4 getMatView() const;
    float fov() const { return lerp(cfg::MIN_FOV, cfg::MAX_FOV, _distanceCursor); }
    Object::PRS &targetPRS() { return _target.prs(); }

    void update() override;
    void reset();
    void zoomIn(float delta);
    void moveFront(float delta);
    void moveLeft(float delta);
    void moveUp(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);

private:
    float &distanceCursor() { return _distanceCursor; }
    float distanceCursor() const { return _distanceCursor; }
    float distance() const;
    void updatePosOffset();
    float maxPosOffsetX() const { return POS_OFFSET_ANGLE_FACTOR * distance(); }
    float maxPosOffsetY() const { return POS_OFFSET_ANGLE_FACTOR * distance(); }

};

}


#endif //LIHOWAR_TRACKBALLCAMERA_HPP
