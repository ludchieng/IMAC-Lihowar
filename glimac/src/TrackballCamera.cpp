#include "glimac/TrackballCamera.hpp"

TrackballCamera::TrackballCamera()
    : m_fDistance(0), m_fAngleX(0), m_fAngleY(0) {}

TrackballCamera::TrackballCamera(float fDist, float fAngX, float fAngY)
    : m_fDistance(fDist), m_fAngleX(fAngX), m_fAngleY(fAngY) {}

TrackballCamera::~TrackballCamera() {}

glm::mat4 TrackballCamera::getViewMatrix() const {
    glm::mat4 res = glm::mat4(1);
    res = glm::translate(res, glm::vec3(0.f, 0.f, -m_fDistance));
    res = glm::rotate(res, glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f));
    res = glm::rotate(res, glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f));
    return res;
}

void TrackballCamera::moveFront(float delta) {
    m_fDistance *= delta;
}

void TrackballCamera::rotateLeft(float degrees) {
    m_fAngleY += degrees;
}

void TrackballCamera::rotateUp(float degrees) {
    m_fAngleX += degrees;
}
