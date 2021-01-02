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
#ifndef LIHOWAR_OBJECTDYNAMIC_HPP
#define LIHOWAR_OBJECTDYNAMIC_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Object.hpp>
#include <lihowarlib/Material.hpp>

namespace lihowar {

/**
 * @brief Represents a dynamic game object in a game scene
 *
 * A ObjectDynamic can moves through the scene following the
 * rules of solid mechanics
 */
class ObjectDynamic : public Object {

private:
    /**
     * @brief Mass per unit volume
     */
    static constexpr float MASS_DENSITY = 10.f;

    /**
     * @brief Inertia coefficient
     */
    static constexpr float INERTIA_COEF = 1.f;

    /**
     * @brief Minimum distance between the center of mass
     * and a force application point to cause a mechanical
     * torque action
     */
    static constexpr float TORQUE_MIN_DIST = .01f;

    /**
     * @brief Linear velocity drag coefficient
     */
    static constexpr float LINEAR_DRAG_COEF = 100.f;

    /**
     * @brief Angular velocity drag coefficient
     */
    static constexpr float ANGULAR_DRAG_COEF = 200.f;

    /**
     * @brief Linear velocity minimum value to cause
     * the object to translate
     */
    static constexpr float LINEAR_VELOCITY_SLIP_LIMIT = .00002f;

    /**
     * @brief Angular velocity minimum value to cause
     * the object to rotate
     */
    static constexpr float ANGULAR_VELOCITY_SLIP_LIMIT = .0000004f;

protected:
    // MEMBERS

    /**
     * @brief Mass of the game object without its sub-objects
     */
    float _mass;

    /**
     * @brief Mass of the game object and its sub-objects
     */
    float _totalMass;

    /**
     * @brief Inertia of the game object
     *
     * Inertia is the resistance to rotation
     */
    glm::vec3 _inertia;

    /**
     * @brief Linear acceleration vector
     */
    glm::vec3 _acc;

    /**
     * @brief Linear velocity vector
     */
    glm::vec3 _vel;

    /**
     * @brief Angular acceleration vector
     */
    glm::vec3 _angAcc;

    /**
     * @brief Angular velocity vector
     */
    glm::vec3 _angVel;

public:
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief ObjectDynamic class constructor
     * @param mesh
     * @param textureId  Diffuse texture GL ID
     * @param prs           Position, rotation and scale state
     */
    explicit ObjectDynamic(
            Mesh& mesh,
            GLuint textureId = 0,
            PRS prs = PRS())
       :Object(mesh, textureId, prs)
    {
        updateMass();
        updateInertia();
        updateTotalMass();
    }

    /**
     * @brief ObjectDynamic class constructor
     * @param mesh
     * @param material
     * @param prs       Position, rotation and scale state
     */
    explicit ObjectDynamic(
            Mesh& mesh,
            Material &material,
            PRS prs = PRS())
       :Object(mesh, material, prs)
    {
        updateMass();
        updateInertia();
        updateTotalMass();
    }

public:
    // INTERFACE
    float mass() const { return _mass; }
    const glm::vec3 & inertia() const { return _inertia; }
    const glm::vec3 &acc() const { return _acc; }
    const glm::vec3 &vel() const { return _vel; }
    const glm::vec3 &angAcc() const { return _angAcc; }
    const glm::vec3 &angVel() const { return _angVel; }
    float totalMass() const { return _totalMass; }

    /**
     * @brief Asserts the game object is not moving
     * @return Returns true if the game object is not moving, false otherwise
     */
    bool isStatic() const;


    /**
     * @brief Adds a sub-object
     * @param object  Object to add as sub-object
     */
    void add(std::unique_ptr<Object> object) override;


    /**
     * @brief Updates state of the Object
     */
    void update() override;

    /**
     * @brief Apply a Newtonian force on the game object
     * at its center of mass
     * @param force  Force vector
     */
    virtual void applyForce(const glm::vec3 &force);

    /**
     * @brief Apply a Newtonian force on the game object
     * at a specified point of application
     * @param force               Force vector
     * @param pointOfApplication  Point of application (in the world basis)
     */
    virtual void applyForce(
            const glm::vec3 &force,
            const glm::vec3 &pointOfApplication);

    /**
     * @brief Apply a torque on the game object at its
     * center of mass
     * @param torque  Torque vector
     */
    virtual void applyTorque(const glm::vec3 &torque);

    /**
     * @brief Updates the mechanics of the game object
     */
    virtual void updateDynamic();

private:
    void applyLinearDrag();
    void applyAngularDrag();
    void updateMass();
    void updateInertia();
    void updateTotalMass();
};

}


#endif //LIHOWAR_OBJECTDYNAMIC_HPP
