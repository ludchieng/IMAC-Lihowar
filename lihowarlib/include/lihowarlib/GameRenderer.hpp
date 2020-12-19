#ifndef LIHOWAR_GAMERENDERER_HPP
#define LIHOWAR_GAMERENDERER_HPP

#include <GL/glew.h>
#include <lihowarlib/common.hpp>
#include <lihowarlib/TrackballCamera.hpp>
#include <lihowarlib/programs/Program.hpp>
#include <lihowarlib/Object.hpp>
#include <lihowarlib/Scene.hpp>
#include <lihowarlib/designpattern/Observer.hpp>

namespace lihowar {

class GameRenderer : public dp::Observer {

private:
    // MEMBERS
    TrackballCamera _tbcam;
    glm::mat4 _matProj;
    glm::mat4 _matMV;
    glm::mat4 _matNormal;
    glm::mat4 _matView;
    Program *_program;

private:
    // CONSTRUCTORS & DESTRUCTORS
    GameRenderer(glm::vec3 &camTarget);
    ~GameRenderer() override;

public:
    /// \brief get instance of the GameRenderer singleton class
    static GameRenderer& instance(glm::vec3 &camTarget) {
        static GameRenderer instance(camTarget);
        return instance;
    }
    // prevent instance duplication
    GameRenderer(const GameRenderer&) = delete;
    GameRenderer(GameRenderer&&) = delete;
    GameRenderer& operator=(const GameRenderer&) = delete;
    GameRenderer& operator=(GameRenderer&&) = delete;
    
public:
    // INTERFACE
    TrackballCamera &camera() { return _tbcam; };
    void use(Program &program);
    void update();
    void updateMatMV(const glm::mat4 &matModel = glm::mat4(1.));
    void updateMatProj();
    void bindUniformVariables(const Object &object, const Scene &scene);

};

}


#endif //LIHOWAR_GAMERENDERER_HPP
