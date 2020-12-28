#ifndef LIHOWAR_PLAYER_HPP
#define LIHOWAR_PLAYER_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/designpattern/Subject.hpp>
#include <lihowarlib/designpattern/Observer.hpp>
#include <lihowarlib/ObjectDynamic.hpp>
#include <lihowarlib/AssetManager.hpp>

namespace lihowar {

class Player : public ObjectDynamic, public dp::Subject {
    friend class SceneSerializer;

public:
    static constexpr float LINEAR_ACC_Y = .0004;
    static constexpr float LINEAR_ACC_X = .0008;
    static constexpr float LINEAR_ACC_Z = .0012;
    static constexpr float YAW_ACC = .0000005;
    static constexpr float PITCH_ACC = .000001;
    static constexpr float ROLL_ACC = .000001;

protected:
    // MEMBERS

public:
    // CONSTRUCTORS & DESTRUCTORS
    Player()
       :ObjectDynamic(
          *AssetManager::mesh(MeshName::AIRSHIP_BALLOON),
          *new Material(
                  AssetManager::texId(TextureName::AIRSHIP_BALLOON_DIFF), 0, 0,
                  AssetManager::texId(TextureName::AIRSHIP_BALLOON_AO),
                  AssetManager::texId(TextureName::AIRSHIP_BALLOON_NORMAL) )
         ,PRS(glm::vec3(321.468,   -7.734,  101.896))
         //,PRS(glm::vec3(666.580,  -28.709, -182.077)
         )
    {
        Object::add(new Object(
                *AssetManager::mesh(MeshName::AIRSHIP_NACELLE),
                *new Material(
                        AssetManager::texId(TextureName::AIRSHIP_NACELLE_DIFF), 0, 0,
                        AssetManager::texId(TextureName::AIRSHIP_NACELLE_AO),
                        AssetManager::texId(TextureName::AIRSHIP_NACELLE_NORMAL) )  ));

        Object::add(new Object(
                *AssetManager::mesh(MeshName::AIRSHIP_WOODFLOOR),
                *new Material(
                        AssetManager::texId(TextureName::AIRSHIP_WOODFLOOR_DIFF), 0, 0,
                        AssetManager::texId(TextureName::AIRSHIP_WOODFLOOR_AO) )  ));
    }
    
public:
    // INTERFACE
    float longitudinalVel() const;

    void move(const glm::vec3 &acc) { _acc += acc; }
    void moveForward(float acc = 1.)   { move( glm::vec3(acc * LINEAR_ACC_Z * glm::rotate(glm::mat4(1.), _prs.rotRadians().y, PRS::Y) * -PRS::vec4_Z )); }
    void moveBackward(float acc = 1.)  { moveForward(-acc); }
    void moveLeftward(float acc = 1.)  { move( glm::vec3(acc * LINEAR_ACC_X * glm::rotate(glm::mat4(1.), _prs.rotRadians().y, PRS::Y) * -PRS::vec4_X )); }
    void moveRightward(float acc = 1.) { moveLeftward(-acc); }
    void moveUpward(float acc = 1.)    { move( acc * LINEAR_ACC_Y * glm::vec3(0.,1.,0.) ); }
    void moveDownward(float acc = 1.)  { moveUpward(-acc); }

    void yaw(float acc) { _angAcc += acc * YAW_ACC * glm::vec3(0., 1., 0.); }
    void yawClockwise(float acc = 1.)     { yaw(-acc); }
    void yawAntiClockwise(float acc = 1.) { yaw(acc); }

    void pitch(float acc) { _angAcc += acc * PITCH_ACC * glm::vec3(1., 0., 0.); }
    void pitchUp(float acc = 1.)   { pitch(acc); }
    void pitchDown(float acc = 1.) { pitch(-acc); }

    void roll(float acc) { _angAcc += acc * ROLL_ACC * glm::vec3(0., 0., 1.); }
    void rollClockwise(float acc = 1.)     { roll(-acc); }
    void rollAntiClockwise(float acc = 1.) { roll(acc); }


    void add(std::unique_ptr<Object> object) override;
    void applyForce(const glm::vec3 &force) override;
    void applyForce(
            const glm::vec3 &force,
            const glm::vec3 &pointOfApplication) override;
    void applyTorque(const glm::vec3 &torque) override;


};

}


#endif //LIHOWAR_PLAYER_HPP
