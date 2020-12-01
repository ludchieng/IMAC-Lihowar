#pragma once

#include <glimac/glm.hpp>

class FreeflyCamera {
private:
    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;

public:
    FreeflyCamera();
    FreeflyCamera(glm::vec3 pos, float fPhi, float fTheta);
    ~FreeflyCamera();

    glm::mat4 getViewMatrix() const;

    void computeDirectionVectors();

    void moveLeft(float delta);
    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
};