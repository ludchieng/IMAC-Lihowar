#ifndef LIHOWAR_OBJECTDYNAMIC_HPP
#define LIHOWAR_OBJECTDYNAMIC_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/Object.hpp>

namespace lihowar {

class ObjectDynamic : public Object {

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
       :Object(mesh, textureId, prs),
        _mass(MASS_DENSITY * _mesh.size().x * mesh.size().y * mesh.size().z),
        _inertia( INERTIA_COEF * glm::vec3(_mesh.size().x, mesh.size().y,  mesh.size().z) )
    {
        updateTotalMass();
    }

public:
    // INTERFACE
    float totalMass() const { return _totalMass; }
    bool isStatic() const;

    void add(std::unique_ptr<Object> object) override;
    void add(Object *object) override { add(std::unique_ptr<Object>(object)); }

    void update() override;
    void applyForce(const glm::vec3 &force);
    void applyForce(
            const glm::vec3 &force,
            const glm::vec3 &pointOfApplication);
    void applyTorque(const glm::vec3 &torque);
    void updateDynamic();

private:
    void applyLinearDrag();
    void applyAngularDrag();
    void updateTotalMass();
};

}


#endif //LIHOWAR_OBJECTDYNAMIC_HPP
