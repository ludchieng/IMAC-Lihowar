#include "glimac/FreeflyCamera.hpp"


FreeflyCamera::FreeflyCamera()
  : m_Position(glm::vec3(0.)), m_fPhi(glm::pi<float>()), m_fTheta(0.) {
    computeDirectionVectors();
}

FreeflyCamera::FreeflyCamera(glm::vec3 pos, float fPhi, float fTheta)
  : m_Position(pos), m_fPhi(fPhi), m_fTheta(fTheta) {
    computeDirectionVectors();
}

FreeflyCamera::~FreeflyCamera() {}

#include <iostream>

glm::mat4 FreeflyCamera::getViewMatrix() const {
    return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
}

void FreeflyCamera::computeDirectionVectors() {
    m_FrontVector = glm::vec3(
        glm::cos(m_fTheta) * glm::sin(m_fPhi),
        glm::sin(m_fTheta),
        glm::cos(m_fTheta) * glm::cos(m_fPhi)
    );
    m_LeftVector = glm::vec3(
        glm::sin(m_fPhi + glm::half_pi<float>()),
        0,
        glm::cos(m_fPhi + glm::half_pi<float>())
    );
    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

void FreeflyCamera::moveLeft(float delta) {
    m_Position += delta * m_LeftVector;
    computeDirectionVectors();
}

void FreeflyCamera::moveFront(float delta) {
    m_Position += delta * m_FrontVector;
    computeDirectionVectors();
}

void FreeflyCamera::rotateLeft(float degrees) {
    m_fPhi += glm::radians(degrees);
    computeDirectionVectors();
}

void FreeflyCamera::rotateUp(float degrees) {
    m_fTheta += glm::radians(degrees);
    computeDirectionVectors();
}
