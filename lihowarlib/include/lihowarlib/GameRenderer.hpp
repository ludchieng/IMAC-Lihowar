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
#ifndef LIHOWAR_GAMERENDERER_HPP
#define LIHOWAR_GAMERENDERER_HPP

#include <GL/glew.h>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/TrackballCamera.hpp>
#include <lihowarlib/programs/Program.hpp>
#include <lihowarlib/Object.hpp>
#include <lihowarlib/Scene.hpp>

namespace lihowar {

/**
 * @brief Singleton class for game rendering
 */
class GameRenderer {

private:
    // MEMBERS

    /**
     * @brief Track ball camera instance
     */
    TrackballCamera _tbcam;

    /**
     * @brief Projection matrix
     */
    glm::mat4 _matProj;

    /**
     * @brief Model View matrix
     */
    glm::mat4 _matMV;

    /**
     * @brief Normal matrix
     */
    glm::mat4 _matNormal;

    /**
     * @brief View matrix
     */
    glm::mat4 _matView;

    /**
     * @brief Currently active GLSL program
     */
    Program *_program;

private: // singleton
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief GameRenderer constructor
     * @param camTarget
     */
    explicit GameRenderer(Object &camTarget);
    ~GameRenderer() = default;

public:
    /**
     * @brief Gets instance of the GameRenderer singleton class
     */
    static GameRenderer& instance(Object &camTarget) {
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

    /**
     * @brief Gets the camera
     * @return Returns the camera
     */
    TrackballCamera &camera() { return _tbcam; };


    /**
     * @brief Changes the currently running GLSL program
     * to requested one
     * @param program  GLSL program to activate
     */
    void use(Program &program);

    /**
     * @brief Updates state of GameRenderer
     */
    void update();

    /**
     * @brief Updates the Model View matrix
     * @param matModel  Model matrix
     */
    void updateMatMV(const glm::mat4 &matModel = glm::mat4(1.));

    /**
     * @brief Updates the Projection matrix
     */
    void updateMatProj();


    /**
     * @brief Renders the game scene
     * @param scene  Scene to render
     */
    void render(const Scene &scene);

    /**
     * @brief Send GLSL uniform variables to GPU
     * @param object  Game object to render
     * @param scene   Current game scene
     */
    void bindUniformVariables(const Object &object, const Scene &scene);

private:
    /**
     * @brief Renders a list of game objects
     * @param scene           Current game scene
     * @param objectsList     List of game objects to render
     * @param matModelParent  Model matrix of a potential parent object
     */
    void render(
            const Scene &scene,
            const std::list< std::unique_ptr<Object> > &objectsList,
            const glm::mat4 &matModelParent = glm::mat4(1.));

    /**
     * @brief Renders a vector of game objects
     * @param scene           Current game scene
     * @param objectsList     Vector of game objects to render
     * @param matModelParent  Model matrix of a potential parent object
     */
    void render(
            const Scene &scene,
            const std::vector< std::unique_ptr<Island> > &objectsList,
            const glm::mat4 &matModelParent = glm::mat4(1.));

    /**
     * @brief Renders a game Scene
     * @param scene           Current game scene
     * @param object          Game objet to render
     * @param matModelParent  Model matrix of a potential parent object
     */
    void render(
            const Scene &scene,
            const Object &object,
            const glm::mat4 &matModelParent = glm::mat4(1.));

    void bindUniformVariablesDirLightProgram(const Object &object, const Scene &scene);
    void bindUniformVariablesIslandProgram(const Object &object, const Scene &scene);
    void bindUniformVariablesMultiLightsProgram(const Object &object, const Scene &scene);

};

}


#endif //LIHOWAR_GAMERENDERER_HPP
