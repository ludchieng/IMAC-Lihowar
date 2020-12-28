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
