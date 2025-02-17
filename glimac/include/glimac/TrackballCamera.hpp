#pragma once

#include <glimac/glm.hpp>

class TrackballCamera {
private:
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;

public:
    TrackballCamera();
    TrackballCamera(float fDist, float fAngX, float fAngY);
    ~TrackballCamera();

    glm::mat4 getViewMatrix() const;

    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);

};