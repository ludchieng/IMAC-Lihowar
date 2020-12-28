#include <lihowarlib/TrackballCamera.hpp>
#include <cmath>

using namespace std;
using namespace lihowar;

namespace lihowar {

const std::function<float(float, float, float)>
TrackballCamera::lerp = [](float start, float stop, float amount) {
    return amount * (stop-start) + start;
};


// Ease in out function for distance variation
const std::function<float(float, float, float, float)>
TrackballCamera::easeQuad = [](float x, float maxX, float offsetY, float maxY) {
    x /= maxX * .5f;
    if (x < 1) return (maxY-offsetY)*.5*x*x + offsetY;
    x--;
    return -(maxY-offsetY)*.5 * (x*(x-2) - 1) + offsetY;
};


const std::function<float(float, float, float, float)>
TrackballCamera::easeCos = [](float x, float maxX, float offsetY, float maxY) {
    return -(maxY-offsetY)*.5 * (cos(M_PI*x/maxX) - 1) + offsetY;
};



TrackballCamera::TrackballCamera(
        Player &target,
        float distanceCursor,
        glm::vec3 ang)
   :_target(target),
    _distanceCursor(distanceCursor),
    _ang(ang)
{
    // Design pattern observer on target player
    addSubject(&_target);
}


glm::mat4 TrackballCamera::getMatView() const
{
    glm::mat4 res = glm::mat4(1.f);
    res = glm::translate(res, glm::vec3(0.f, 0.f, - distance()));
    res = glm::translate(res, _posOffset);
    res = glm::rotate(res, glm::radians(_ang.x + _angOffset.x), glm::vec3(1.f, 0.f, 0.f));
    res = glm::rotate(res, glm::radians(-_target.prs().rot().y), glm::vec3(0.f, 1.f, 0.f));
    res = glm::rotate(res, glm::radians(_ang.y + _angOffset.y), glm::vec3(0.f, 1.f, 0.f));
    res = glm::translate( res, -_target.prs().pos());
    return res;
}


float TrackballCamera::distance() const
{
    return easeCos(
            _distanceCursor,
            MAX_DISTANCE_CURSOR,
            MIN_DISTANCE,
            MAX_DISTANCE);
}


void TrackballCamera::update()
{
    _angOffset.x = glm::clamp(_target.vel().y * -ANG_OFFSET_X_COEF, ANG_OFFSET_XY_MIN, ANG_OFFSET_XY_MAX);
    _angOffset.y = glm::clamp(_target.angVel().y * ANG_OFFSET_Y_COEF, ANG_OFFSET_XY_MIN, ANG_OFFSET_XY_MAX);
    _posOffset.z = _target.longitudinalVel() * _distanceCursor * -POS_OFFSET_Z_COEF;
    updatePosOffset();
}


void TrackballCamera::reset()
{
    _distanceCursor = DEFAULT_DISTANCE_CURSOR;
    _posOffset = glm::vec3(0.);
    _angOffset = glm::vec3(0.);
    _ang.x = DEFAULT_ANGLE_X;
    _ang.y = DEFAULT_ANGLE_Y;
}


void TrackballCamera::zoomIn(float delta)
{
    _distanceCursor = glm::clamp(_distanceCursor + delta, MIN_DISTANCE_CURSOR, MAX_DISTANCE_CURSOR);
    updatePosOffset();
}


void TrackballCamera::moveFront(float delta)
{
    _posOffset.z -= delta;
    updatePosOffset();
}


void TrackballCamera::moveLeft(float delta)
{
    _posOffset.x -= delta;
    updatePosOffset();
}


void TrackballCamera::moveUp(float delta)
{
    _posOffset.y -= delta;
    updatePosOffset();
}


void TrackballCamera::rotateLeft(float degrees)
{
    _ang.y += degrees;
}


void TrackballCamera::rotateUp(float degrees)
{
    _ang.x += degrees;
}

void TrackballCamera::updatePosOffset()
{
    _posOffset.x = glm::clamp(_posOffset.x, -maxPosOffsetX(), maxPosOffsetX());
    _posOffset.y = glm::clamp(_posOffset.y, -maxPosOffsetY(), maxPosOffsetY());
    _posOffset.z = glm::clamp(_posOffset.z, POS_OFFSET_Z_MIN, POS_OFFSET_Z_MAX);
}

}