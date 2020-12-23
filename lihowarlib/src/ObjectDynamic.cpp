#include <lihowarlib/ObjectDynamic.hpp>

using namespace std;
using namespace lihowar;

namespace lihowar {

glm::mat3 projectOnXY = glm::mat3(
        glm::vec3(1., 0., 0.),
        glm::vec3(0., 1., 0.),
        glm::vec3(0., 0., 0.) );

glm::mat3 projectOnXZ = glm::mat3(
        glm::vec3(1., 0., 0.),
        glm::vec3(0., 0., 0.),
        glm::vec3(0., 0., 1.) );

glm::mat3 projectOnYZ = glm::mat3(
        glm::vec3(0., 0., 0.),
        glm::vec3(0., 1., 0.),
        glm::vec3(0., 0., 1.) );



bool ObjectDynamic::isStatic() const
{
    return glm::length(_vel) == 0.f
        && glm::length(_acc) == 0.f
        && glm::length(_angAcc) == 0.f
        && glm::length(_angVel) == 0.f;
}


void ObjectDynamic::add(std::unique_ptr<Object> object)
{
    _subobjects.push_back(std::move(object));
    updateTotalMass();
}


void ObjectDynamic::applyForce(const glm::vec3 &force)
{
    _acc += force / _mass;
}


void ObjectDynamic::applyForce(
        const glm::vec3 &force,
        const glm::vec3 &pointOfApplication)
{
    // if (DEBUG) cout << "[Physics]: apply force: " << force / _mass << endl;
    _acc += force / _mass;
    glm::vec3 distVec = pointOfApplication - _mesh.center();
    if (glm::length(distVec) > TORQUE_MIN_DIST)
        applyTorque( glm::vec3(
                glm::cross( projectOnYZ * distVec, force ).x,
                glm::cross( projectOnXZ * distVec, force ).y,
                glm::cross( projectOnXY * distVec, force ).z  ));
}


void ObjectDynamic::applyTorque(const glm::vec3 &torque)
{
    // if (DEBUG) cout << "[Physics]: apply torque: " << torque / _inertia << endl;
    _angAcc += torque / _inertia;
}


void ObjectDynamic::applyLinearDrag()
{
    glm::vec3 dragDir = -glm::normalize(_vel);
    applyForce( LINEAR_DRAG_COEF * dragDir * glm::pow(glm::length(_vel), 1.5f) );
}


void ObjectDynamic::applyAngularDrag()
{
    glm::vec3 dragAxis = -glm::normalize(_angVel);
    applyTorque( ANGULAR_DRAG_COEF * dragAxis * glm::pow(glm::length(_angVel), 1.5f) );
}


void ObjectDynamic::update()
{
    updateDynamic();
}


void ObjectDynamic::updateDynamic()
{
    if (isStatic())
        return;

    if (glm::length(_vel) >= LINEAR_VELOCITY_SLIP_LIMIT)
        applyLinearDrag();

    _vel += _acc;
    _vel = (glm::length(_vel) < LINEAR_VELOCITY_SLIP_LIMIT) ? glm::vec3(0.) : _vel;
    _prs.pos() += _vel;
    // if (DEBUG) cout << "[Physics]: STATUS: \t\t    acc: " << _acc << " \t\t    vel:" << _vel << " \t\t pos:" << _prs.pos() << endl;
    _acc = glm::vec3(0.);

    if (glm::length(_angVel) >= ANGULAR_VELOCITY_SLIP_LIMIT)
        applyAngularDrag();

    _angVel += _angAcc;
    _angVel = (glm::length(_angVel) < ANGULAR_VELOCITY_SLIP_LIMIT) ? glm::vec3(0.) : _angVel;
    _prs.rot() += 360.f / M_2_PIf32 * _angVel;
    // if (DEBUG) cout << "\t\t angAcc: " << _angAcc << " \t\t angVel:" << _angVel << " \t\t rot:" << _prs.rot() << endl;
    _angAcc = glm::vec3(0.);

}


void ObjectDynamic::updateTotalMass()
{
    float res = 0.f;
    auto it = _subobjects.begin();
    while (it != _subobjects.end()) {
        auto objectDyn = dynamic_cast<ObjectDynamic*>(it->get());
        if (nullptr != objectDyn)
            res += objectDyn->totalMass();
        ++it;
    }
    _totalMass = _mass + res;
}

}