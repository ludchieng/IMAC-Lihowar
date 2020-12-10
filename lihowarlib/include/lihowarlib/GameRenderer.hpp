#ifndef LIHOWAR_GAMERENDERER_HPP
#define LIHOWAR_GAMERENDERER_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/programs/Normal.hpp>
#include <GL/glew.h>

using namespace std;

namespace lihowar {

class GameRenderer {

private:
    // MEMBERS
    glm::mat4 _matProj;
    glm::mat4 _matMV;
    glm::mat4 _matNormal;
    glm::mat4 _matGlobal;

private:
    // CONSTRUCTORS & DESTRUCTORS
    GameRenderer();
    ~GameRenderer() = default;

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
    void useProgram();
    void bindUniformVariables();

};

}


#endif //LIHOWAR_GAMERENDERER_HPP
