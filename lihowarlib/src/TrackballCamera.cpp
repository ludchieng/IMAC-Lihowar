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


glm::mat4 TrackballCamera::getMatView() const
{
    glm::mat4 res = glm::mat4(1.f);
    res = glm::translate(res, glm::vec3(0.f, 0.f, - distance()));
    res = glm::rotate(res, glm::radians(_angleX), glm::vec3(1.f, 0.f, 0.f));
    res = glm::rotate(res, glm::radians(- _targetPRS.rot().y), glm::vec3(0.f, 1.f, 0.f));
    res = glm::rotate(res, glm::radians(_angleY), glm::vec3(0.f, 1.f, 0.f));
    res = glm::translate( res, -_targetPRS.pos());
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


void TrackballCamera::moveFront(float delta)
{
    _distanceCursor = glm::clamp(_distanceCursor + delta, MIN_DISTANCE_CURSOR, MAX_DISTANCE_CURSOR);
    //if (DEBUG) cout << "[TrackballCamera::moveFront] : distance :" << distance() << endl;
    notify(); // notify observers that attributes have changed
}


void TrackballCamera::rotateLeft(float degrees)
{
    _angleY += degrees;
    notify(); // notify observers that attributes have changed
}


void TrackballCamera::rotateUp(float degrees)
{
    _angleX += degrees;
    notify(); // notify observers that attributes have changed
}

}