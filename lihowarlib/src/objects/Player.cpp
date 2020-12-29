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
#include <lihowarlib/objects/Player.hpp>

using namespace lihowar;

namespace lihowar {

Player::Player()
        :ObjectDynamic(
        *AssetManager::mesh(MeshName::AIRSHIP_BALLOON),
        *new Material(
                AssetManager::texId(TextureName::AIRSHIP_BALLOON_DIFF), 0, 0,
                AssetManager::texId(TextureName::AIRSHIP_BALLOON_AO),
                AssetManager::texId(TextureName::AIRSHIP_BALLOON_NORMAL) ),
        PRS(glm::vec3(321.468,   -7.734,  101.896)) )
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
