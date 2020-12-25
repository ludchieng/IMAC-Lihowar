#include <lihowarlib/objects/Player.hpp>

using namespace lihowar;

namespace lihowar {

float Player::longitudinalVel() const
{
    if (glm::length(vel()) == 0.f)
        return 0.f;
    glm::vec4 dir4(0., 0., -1., 0.);
    dir4 = glm::rotate(glm::mat4(1.), _prs.rotRadians().y, PRS::Y) * dir4;
    glm::vec3 dir3 = glm::normalize( glm::vec3(dir4) );
    return glm::dot(vel(), dir3);
}


void Player::add(std::unique_ptr<Object> object)
{
    ObjectDynamic::add(std::move(object));
    notify(); // Notify observers that player's attributes have changed
}


void Player::applyForce(const glm::vec3 &force)
{
    ObjectDynamic::applyForce(force);
    notify(); // Notify observers that player's attributes have changed
}


void Player::applyForce(const glm::vec3 &force, const glm::vec3 &pointOfApplication)
{
    ObjectDynamic::applyForce(force, pointOfApplication);
    notify(); // Notify observers that player's attributes have changed
}


void Player::applyTorque(const glm::vec3 &torque)
{
    ObjectDynamic::applyTorque(torque);
    notify(); // Notify observers that player's attributes have changed
}

}