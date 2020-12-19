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
    const float MIN_DISTANCE_CURSOR = 0.f;
    const float MAX_DISTANCE_CURSOR = 1.f;
    const float MIN_DISTANCE = 1.f;
    const float MAX_DISTANCE = 20.f;
    const static std::function<float(float, float, float)> lerp;
    const static std::function<float(float, float, float, float)> easeQuad;
    const static std::function<float(float, float, float, float)> easeCos;

private:
    // MEMBERS
    glm::vec3 &_target;
    float _distanceCursor;
    float _angleX;
    float _angleY;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit TrackballCamera(
            glm::vec3 &target,
            const float distanceCursor = 0.f,
            const float angX = 0.f,
            const float angY = 0.f)
       :_target(target), _distanceCursor(distanceCursor),
        _angleX(angX), _angleY(angY)
    {}

    ~TrackballCamera() override = default;
    
public:
    // INTERFACE
    glm::mat4 getMatView() const;
    float fov() const { return lerp(MIN_FOV, MAX_FOV, _distanceCursor); }
    glm::vec3 &target() { return _target; }

    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);

private:
    float &distanceCursor() { return _distanceCursor; }
    float distanceCursor() const { return _distanceCursor; }
    float distance() const;

};

}


#endif //LIHOWAR_TRACKBALLCAMERA_HPP
