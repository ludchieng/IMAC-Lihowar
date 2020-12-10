#include <lihowarlib/TrackballCamera.hpp>

using namespace lihowar;

namespace lihowar {

TrackballCamera::TrackballCamera()
        : _fDistance(0), _fAngleX(0), _fAngleY(0) {}

TrackballCamera::TrackballCamera(float fDist, float fAngX, float fAngY)
        : _fDistance(fDist), _fAngleX(fAngX), _fAngleY(fAngY) {}

TrackballCamera::~TrackballCamera() {}

glm::mat4 TrackballCamera::getMatView() const {
    glm::mat4 res = glm::mat4(1);
    res = glm::translate(res, glm::vec3(0.f, 0.f, -_fDistance));
    res = glm::rotate(res, glm::radians(_fAngleX), glm::vec3(1.f, 0.f, 0.f));
    res = glm::rotate(res, glm::radians(_fAngleY), glm::vec3(0.f, 1.f, 0.f));
    return res;
}

void TrackballCamera::moveFront(float delta)
{
    _fDistance *= delta;
    notify(); // notify observers that attributes has changed
}


void TrackballCamera::rotateLeft(float degrees)
{
    _fAngleY += degrees;
    notify(); // notify observers that attributes has changed
}


void TrackballCamera::rotateUp(float degrees)
{
    _fAngleX += degrees;
    notify(); // notify observers that attributes has changed
}

}