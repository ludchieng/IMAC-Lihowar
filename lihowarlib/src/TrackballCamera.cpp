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
        Object &target,
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
    if (_target.isInstanceOf<ObjectDynamic>()) {
        ObjectDynamic &tget = *dynamic_cast<ObjectDynamic*>(&_target);
        // because angle offset only applies on a dynamic target
        _angOffset.x = glm::clamp(tget.vel().y * -ANG_OFFSET_X_KICKBACK_COEF, ANG_OFFSET_XY_MIN, ANG_OFFSET_XY_MAX);
        _angOffset.y = glm::clamp(tget.angVel().y * ANG_OFFSET_Y_KICKBACK_COEF, ANG_OFFSET_XY_MIN, ANG_OFFSET_XY_MAX);
    }
    if (_target.isInstanceOf<Player>()) {
        Player &tget = *dynamic_cast<Player*>(&_target);
        // because position offset only applies on a Player target
        _posOffset.z = tget.longitudinalVel() * _distanceCursor * -POS_OFFSET_KICKBACK_COEF;
        updatePosOffset();
    }
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
