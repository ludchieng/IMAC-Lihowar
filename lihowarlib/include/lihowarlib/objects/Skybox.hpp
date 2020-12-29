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
#ifndef LIHOWAR_SKYBOX_HPP
#define LIHOWAR_SKYBOX_HPP

#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/Object.hpp>
#include <lihowarlib/AssetManager.hpp>
#include <lihowarlib/programs/SkyboxProgram.hpp>

namespace lihowar {

class Skybox : public Object {

private:
    // MEMBERS
    glm::vec3 _ambientColor;
    glm::vec3 _center;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Skybox(float size = 2000.f)
        : Object(
            *AssetManager::mesh(MeshName::CUBE),
            AssetManager::texId(TextureName::SKY),
            Object::PRS(
                glm::vec3(0.),
                glm::vec3(0., 180., -90.),
                glm::vec3(size) )),
          _ambientColor(glm::vec3(.25, .13, .13))
    {}

    ~Skybox() = default;
    
public:
    // INTERFACE
    glm::vec3 ambientColor() { return _ambientColor; }
    void setCenter(const glm::vec3 &center) {
        _center = center;
        prs().pos() = center;
    }

};

}


#endif //LIHOWAR_SKYBOX_HPP
