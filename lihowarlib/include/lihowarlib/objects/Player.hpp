#ifndef LIHOWAR_PLAYER_HPP
#define LIHOWAR_PLAYER_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/ObjectDynamic.hpp>
#include <lihowarlib/AssetManager.hpp>

namespace lihowar {

class Player : public ObjectDynamic {
    friend class SceneSerializer;

public:
    static constexpr float LINEAR_ACC_Y = .06;
    static constexpr float LINEAR_ACC_X = .08;
    static constexpr float LINEAR_ACC_Z = .12;
    static constexpr float YAW_ACC = .0001;
    static constexpr float PITCH_ACC = .00025;
    static constexpr float ROLL_ACC = .00025;

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
    void moveForward(float acc = 1.)   { move( glm::vec3(acc * LINEAR_ACC_Z * glm::rotate(glm::mat4(1.), _prs.rotRadians().y, PRS::Y) * -PRS::vec4_Z )); }
    void moveBackward(float acc = 1.)  { moveForward(-acc); }
    void moveLeftward(float acc = 1.)  { move( glm::vec3(acc * LINEAR_ACC_X * glm::rotate(glm::mat4(1.), _prs.rotRadians().y, PRS::Y) * -PRS::vec4_X )); }
    void moveRightward(float acc = 1.) { moveLeftward(-acc); }
    void moveUpward(float acc = 1.)    { move( acc * LINEAR_ACC_Y * glm::vec3(0.,1.,0.) ); }
    void moveDownward(float acc = 1.)  { moveUpward(-acc); }

    void yaw(float acc) { applyTorque( acc * YAW_ACC * glm::vec3(0., 1., 0.) ); }
    void yawClockwise(float acc = 1.)     { yaw(-acc); }
    void yawAntiClockwise(float acc = 1.) { yaw(acc); }

    void pitch(float acc) { applyTorque( acc * PITCH_ACC * glm::vec3(1., 0., 0.) ); }
    void pitchUp(float acc = 1.)   { pitch(acc); }
    void pitchDown(float acc = 1.) { pitch(-acc); }

    void roll(float acc) { applyTorque( acc * ROLL_ACC * glm::vec3(0., 0., 1.) ); }
    void rollClockwise(float acc = 1.)     { roll(-acc); }
    void rollAntiClockwise(float acc = 1.) { roll(acc); }


};

}


#endif //LIHOWAR_PLAYER_HPP
