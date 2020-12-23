#ifndef LIHOWAR_PLAYER_HPP
#define LIHOWAR_PLAYER_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/ObjectDynamic.hpp>
#include <lihowarlib/AssetManager.hpp>

namespace lihowar {

class Player : public ObjectDynamic {
    friend class SceneSerializer;

public:
    static constexpr float LINEAR_ACC_XZ = .08;
    static constexpr float LINEAR_ACC_Y = .06;
    static constexpr float YAW_ACC = .01;

protected:
    // MEMBERS

public:
    // CONSTRUCTORS & DESTRUCTORS
    Player()
       :ObjectDynamic(
          *AssetManager::instance().meshes()[MeshName::BALLOON] )
    {}
    
public:
    // INTERFACE
    void move(const glm::vec3 &acc) { applyForce(acc); }
    void moveForward(float acc = 1.)   { move( glm::vec3(acc * LINEAR_ACC_XZ * glm::rotate(glm::mat4(1.), _prs.rotRadians().y, PRS::Y) * PRS::vec4_X )); }
    void moveBackward(float acc = 1.)  { move( glm::vec3(acc * LINEAR_ACC_XZ * glm::rotate(glm::mat4(1.), _prs.rotRadians().y, PRS::Y) * -PRS::vec4_X )); }
    void moveLeftward(float acc = 1.)  { move( glm::vec3(acc * LINEAR_ACC_XZ * glm::rotate(glm::mat4(1.), _prs.rotRadians().y, PRS::Y) * -PRS::vec4_Z )); }
    void moveRightward(float acc = 1.) { move( glm::vec3(acc * LINEAR_ACC_XZ * glm::rotate(glm::mat4(1.), _prs.rotRadians().y, PRS::Y) * PRS::vec4_Z )); }
    void moveUpward(float acc = 1.)    { move( acc * LINEAR_ACC_Y * glm::vec3(0.,1.,0.) ); }
    void moveDownward(float acc = 1.)  { move( acc * LINEAR_ACC_Y * glm::vec3(0.,-1.,0.) ); }

    void yaw(float acc) { applyTorque( glm::vec3(0., acc * YAW_ACC, 0.) ); }
    void yawClockwise(float acc = 1.)     { yaw(-acc * YAW_ACC); }
    void yawAntiClockwise(float acc = 1.) { yaw(acc * YAW_ACC); }


};

}


#endif //LIHOWAR_PLAYER_HPP
