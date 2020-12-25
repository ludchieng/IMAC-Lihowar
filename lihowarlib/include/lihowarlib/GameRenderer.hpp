#ifndef LIHOWAR_GAMERENDERER_HPP
#define LIHOWAR_GAMERENDERER_HPP

#include <GL/glew.h>
#include <lihowarlib/GameConfig.hpp>
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
    GameRenderer(Player &camTarget);
    ~GameRenderer() override;

public:
    /// \brief get instance of the GameRenderer singleton class
    static GameRenderer& instance(Player &camTarget) {
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
    void update() override;
    void updateMatMV(const glm::mat4 &matModel = glm::mat4(1.));
    void updateMatProj();
    void render(const Scene &scene);
    void bindUniformVariables(const Object &object, const Scene &scene);

private:
    void render(
            const Scene &scene,
            const std::list< std::unique_ptr<Object> > &objectsList,
            const glm::mat4 &matModelParent = glm::mat4(1.));

    void render(
            const Scene &scene,
            const std::vector< std::unique_ptr<Island> > &objectsList,
            const glm::mat4 &matModelParent = glm::mat4(1.));

    void render(
            const Scene &scene,
            const Object &object,
            const glm::mat4 &matModelParent = glm::mat4(1.));

};

}


#endif //LIHOWAR_GAMERENDERER_HPP
