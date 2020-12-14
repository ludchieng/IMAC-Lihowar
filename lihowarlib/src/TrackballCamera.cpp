#include <lihowarlib/TrackballCamera.hpp>

using namespace lihowar;

namespace lihowar {

TrackballCamera::~TrackballCamera() = default;


glm::mat4 TrackballCamera::getMatView() const
{
    glm::mat4 res = glm::mat4(1);
    res = glm::translate(res, glm::vec3(0.f, 0.f, -_fDistance));
    res = glm::rotate(res, glm::radians(_fAngleX), glm::vec3(1.f, 0.f, 0.f));
    res = glm::rotate(res, glm::radians(_fAngleY), glm::vec3(0.f, 1.f, 0.f));
    return res;
}


void TrackballCamera::moveFront(float delta)
{
    _fDistance *= delta;
    notify(); // notify observers that attributes have changed
}


void TrackballCamera::rotateLeft(float degrees)
{
    _fAngleY += degrees;
    notify(); // notify observers that attributes have changed
}


void TrackballCamera::rotateUp(float degrees)
{
    _fAngleX += degrees;
    notify(); // notify observers that attributes have changed
}

}