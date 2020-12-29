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

class ObjectDynamic : public Object {

private:
    static constexpr float MASS_DENSITY = 10.f;
    static constexpr float INERTIA_COEF = 1.f;
    static constexpr float TORQUE_MIN_DIST = .01f;
    static constexpr float LINEAR_DRAG_COEF = 100.f;
    static constexpr float ANGULAR_DRAG_COEF = 200.f;
    static constexpr float LINEAR_VELOCITY_SLIP_LIMIT = .00002f;
    static constexpr float ANGULAR_VELOCITY_SLIP_LIMIT = .0000004f;

protected:
    // MEMBERS
    float _mass;
    float _totalMass;
    glm::vec3 _inertia;
    glm::vec3 _acc;
    glm::vec3 _vel;
    glm::vec3 _angAcc;
    glm::vec3 _angVel;

public:
    // CONSTRUCTORS & DESTRUCTORS
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
    bool isStatic() const;

    void add(std::unique_ptr<Object> object) override;

    void update() override;

    virtual void applyForce(const glm::vec3 &force);
    virtual void applyForce(
            const glm::vec3 &force,
            const glm::vec3 &pointOfApplication);
    virtual void applyTorque(const glm::vec3 &torque);
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
