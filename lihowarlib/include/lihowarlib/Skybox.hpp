#ifndef LIHOWAR_SKYBOX_HPP
#define LIHOWAR_SKYBOX_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/GameObject.hpp>
#include <lihowarlib/AssetManager.hpp>
#include <lihowarlib/programs/SkyboxProgram.hpp>

namespace lihowar {

class Skybox : public GameObject {

private:
    // MEMBERS
    glm::vec3 _ambientColor;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Skybox(float size = 750.f)
        :GameObject(
            *AssetManager::instance().meshes()[MeshName::CUBE],
            AssetManager::instance().textureId(TextureName::SKY),
            GameObject::PRS(
                glm::vec3(0.),
                glm::vec3(0., 180., -90.),
                glm::vec3(size) ),
            SkyboxProgram::instance()),
         _ambientColor(glm::vec3(.25, .13, .13))
    {}

    ~Skybox() = default;
    
public:
    // INTERFACE
    glm::vec3 ambientColor() { return _ambientColor; }

};

}


#endif //LIHOWAR_SKYBOX_HPP
