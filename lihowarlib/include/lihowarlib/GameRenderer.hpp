#ifndef LIHOWAR_GAMERENDERER_HPP
#define LIHOWAR_GAMERENDERER_HPP

#include <GL/glew.h>
#include <lihowarlib/common.hpp>
#include <lihowarlib/programs/NormalProgram.hpp>
#include <lihowarlib/TrackballCamera.hpp>
#include <lihowarlib/designpattern/Observer.hpp>

namespace lihowar {

class GameRenderer : public dp::Observer {

private:
    // MEMBERS
    glm::mat4 _matProj;
    glm::mat4 _matMV;
    glm::mat4 _matNormal;
    glm::mat4 _matView;
    TrackballCamera _tbcam;

private:
    // CONSTRUCTORS & DESTRUCTORS
    GameRenderer();
    ~GameRenderer() override;

public:
    /// \brief get instance of the GameRenderer singleton class
    static GameRenderer& instance() {
        static GameRenderer instance;
        return instance;
    }
    // prevent instance duplication
    GameRenderer(const GameRenderer&) = delete;
    GameRenderer(GameRenderer&&) = delete;
    GameRenderer& operator=(const GameRenderer&) = delete;
    GameRenderer& operator=(GameRenderer&&) = delete;
    
public:
    // INTERFACE
    void update();
    void updateMatMV(const glm::mat4 &matModel = glm::mat4(1.));
    TrackballCamera &camera() { return _tbcam; };
    void bindUniformMatrices(const Program &program);

};

}


#endif //LIHOWAR_GAMERENDERER_HPP
