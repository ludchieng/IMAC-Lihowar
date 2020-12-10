#ifndef LIHOWAR_TRACKBALLCAMERA_HPP
#define LIHOWAR_TRACKBALLCAMERA_HPP

#include <lihowarlib/common.hpp>

namespace lihowar {

class TrackballCamera {

public:
    // MEMBERS
    float _fDistance;
    float _fAngleX;
    float _fAngleY;

public:
    // CONSTRUCTORS & DESTRUCTORS
    TrackballCamera();
    TrackballCamera(float fDist, float fAngX, float fAngY);
    ~TrackballCamera();
    
public:
    // INTERFACE
    glm::mat4 getMatView() const;

    void moveFront(float delta) { _fDistance *= delta; }
    void rotateLeft(float degrees) { _fAngleY += degrees; }
    void rotateUp(float degrees) { _fAngleX += degrees; }

};

}


#endif //LIHOWAR_TRACKBALLCAMERA_HPP
