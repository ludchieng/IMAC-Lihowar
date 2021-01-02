/*
 *  Copyright (c) 2020-2021 Lihowar
 *
 *  This software is licensed under OSEF License.
 *
 *  The "Software" is defined as the pieces of code, the documentation files, the config
 *  files, the textures assets, the Wavefront OBJ assets, the screenshot image, the sound
 *  effects and music associated with.
 *
 *  This Software is licensed under OSEF License which means IN ACCORDANCE WITH THE LICENSE
 *  OF THE DEPENDENCIES OF THE SOFTWARE, you can use it as you want for any purpose, but
 *  it comes with no guarantee of any kind, provided that you respects the license of the
 *  software dependencies of the piece of code you want to reuse. The dependencies are
 *  listed at the end of the README given in the directory root of the Lihowar repository.
 */
#pragma once
#ifndef LIHOWAR_PLAYER_HPP
#define LIHOWAR_PLAYER_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/ObjectDynamic.hpp>
#include <lihowarlib/AssetManager.hpp>

namespace lihowar {

/**
 * @brief Represents a player game object
 */
class Player : public ObjectDynamic {

public:
    // CONSTANTS

    /**
     * @brief Linear acceleration value on player's Y axis
     */
    static constexpr float LINEAR_ACC_Y = .0004;

    /**
     * @brief Linear acceleration value on player's X axis
     */
    static constexpr float LINEAR_ACC_X = .0008;

    /**
     * @brief Linear acceleration value on player's Z axis
     */
    static constexpr float LINEAR_ACC_Z = .0012;

    /**
     * @brief Angular acceleration value on player's Y axis
     */
    static constexpr float YAW_ACC = .0000005;

    /**
     * @brief Angular acceleration value on player's X axis
     */
    static constexpr float PITCH_ACC = .000001;

    /**
     * @brief Angular acceleration value on player's Z axis
     */
    static constexpr float ROLL_ACC = .000001;

protected:
    // MEMBERS

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief Player class constructor
     */
    Player();
    
public:
    // INTERFACE

    /**
     * @brief Gets the speed on the player's Z axis
     * @return Returns the speed on the player's Z axis
     */
    float longitudinalVel() const;

    /**
     * @brief Applies linear acceleration
     * @param acc  Acceleration vector to apply
     */
    void move(const glm::vec3 &acc) { _acc += acc; }
    void moveForward(float acc = 1.)   { move( glm::vec3(acc * LINEAR_ACC_Z * glm::rotate(glm::mat4(1.), _prs.rotRadians().y, PRS::Y) * -PRS::vec4_Z )); }
    void moveBackward(float acc = 1.)  { moveForward(-acc); }
    void moveLeftward(float acc = 1.)  { move( glm::vec3(acc * LINEAR_ACC_X * glm::rotate(glm::mat4(1.), _prs.rotRadians().y, PRS::Y) * -PRS::vec4_X )); }
    void moveRightward(float acc = 1.) { moveLeftward(-acc); }
    void moveUpward(float acc = 1.)    { move( acc * LINEAR_ACC_Y * glm::vec3(0.,1.,0.) ); }
    void moveDownward(float acc = 1.)  { moveUpward(-acc); }

    /**
     * @brief Applies angular acceleration on player's Y axis
     * @param acc  Acceleration to apply
     */
    void yaw(float acc) { _angAcc += acc * YAW_ACC * glm::vec3(0., 1., 0.); }
    void yawClockwise(float acc = 1.)     { yaw(-acc); }
    void yawAntiClockwise(float acc = 1.) { yaw(acc); }

    /**
     * @brief Applies angular acceleration on player's X axis
     * @param acc  Acceleration to apply
     */
    void pitch(float acc) { _angAcc += acc * PITCH_ACC * glm::vec3(1., 0., 0.); }
    void pitchUp(float acc = 1.)   { pitch(acc); }
    void pitchDown(float acc = 1.) { pitch(-acc); }

    /**
     * @brief Applies angular acceleration on player's Z axis
     * @param acc  Acceleration to apply
     */
    void roll(float acc) { _angAcc += acc * ROLL_ACC * glm::vec3(0., 0., 1.); }
    void rollClockwise(float acc = 1.)     { roll(-acc); }
    void rollAntiClockwise(float acc = 1.) { roll(acc); }


    /**
     * @brief Adds a sub-objects
     * @param object  Sub-object to add
     */
    void add(std::unique_ptr<Object> object) override;

    /**
     * @brief Apply a Newtonian force on the game object
     * at its center of mass
     * @param force  Force vector
     */
    void applyForce(const glm::vec3 &force) override;

    /**
     * @brief Apply a Newtonian force on the game object
     * at a specified point of application
     * @param force               Force vector
     * @param pointOfApplication  Point of application (in the world basis)
     */
    void applyForce(
            const glm::vec3 &force,
            const glm::vec3 &pointOfApplication) override;

    /**
     * @brief Apply a torque on the game object at its
     * center of mass
     * @param torque  Torque vector
     */
    void applyTorque(const glm::vec3 &torque) override;


};

}


#endif //LIHOWAR_PLAYER_HPP
