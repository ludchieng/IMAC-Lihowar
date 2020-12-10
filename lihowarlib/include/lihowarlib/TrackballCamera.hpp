#ifndef LIHOWAR_TRACKBALLCAMERA_HPP
#define LIHOWAR_TRACKBALLCAMERA_HPP

#include <vector>
#include <lihowarlib/common.hpp>
#include <lihowarlib/designpattern/Subject.hpp>

namespace lihowar {

class TrackballCamera : public dp::Subject {

public:
    // MEMBERS
    float _fDistance;
    float _fAngleX;
    float _fAngleY;

public:
    // CONSTRUCTORS & DESTRUCTORS
    TrackballCamera();
    TrackballCamera(float fDist, float fAngX, float fAngY);
    ~TrackballCamera() override;
    
public:
    // INTERFACE
    glm::mat4 getMatView() const;

    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);

};

}


#endif //LIHOWAR_TRACKBALLCAMERA_HPP
