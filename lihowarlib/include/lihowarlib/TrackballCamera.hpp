#ifndef LIHOWAR_TRACKBALLCAMERA_HPP
#define LIHOWAR_TRACKBALLCAMERA_HPP

#include <functional>
#include <lihowarlib/common.hpp>
#include <lihowarlib/designpattern/Subject.hpp>
#include <lihowarlib/designpattern/Observer.hpp>
#include <lihowarlib/Object.hpp>
#include <utility>

namespace lihowar {

class TrackballCamera : public dp::Subject {

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
    const static std::function<float(float, float, float)> lerp;
    const static std::function<float(float, float, float, float)> easeQuad;
    const static std::function<float(float, float, float, float)> easeCos;

private:
    // MEMBERS
    Object::PRS &_targetPRS;
    glm::vec3 _posOffset;
    float _distanceCursor;
    float _angleX;
    float _angleY;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit TrackballCamera(
            Object::PRS &targetPRS,
            const float distanceCursor = DEFAULT_DISTANCE_CURSOR,
            const float angX = DEFAULT_ANGLE_X,
            const float angY = DEFAULT_ANGLE_Y)
       :_targetPRS(targetPRS), _distanceCursor(distanceCursor),
        _angleX(angX), _angleY(angY)
    {}

    ~TrackballCamera() override = default;
    
public:
    // INTERFACE
    glm::mat4 getMatView() const;
    float fov() const { return lerp(MIN_FOV, MAX_FOV, _distanceCursor); }
    Object::PRS &targetPRS() { return _targetPRS; }

    void reset();
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
