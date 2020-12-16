#ifndef LIHOWAR_GAMEOBJECTTEXTURED_HPP
#define LIHOWAR_GAMEOBJECTTEXTURED_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/GameObject.hpp>

namespace lihowar {

class GameObjectTextured : public GameObject {

private:
    // MEMBERS
    GLuint _texId;

public:
    // CONSTRUCTORS & DESTRUCTORS
    explicit GameObjectTextured(
            Mesh& mesh,
            GLuint textureId = 0,
            Program &program = NormalProgram::instance(),
            PRS prs = PRS())
       :GameObject(mesh, program, prs),
        _texId(textureId)
    {}
    
public:
    // INTERFACE
    GLuint &textureId() { return _texId; }
    void render() override;
};

}


#endif //LIHOWAR_GAMEOBJECTTEXTURED_HPP
