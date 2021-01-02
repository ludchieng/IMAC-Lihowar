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
#ifndef LIHOWAR_PROGRAM_IPROGRAM_HPP
#define LIHOWAR_PROGRAM_IPROGRAM_HPP

#include <glimac/Program.hpp>
#include <lihowarlib/GameConfig.hpp>

namespace lihowar {

/**
 * @brief Enumeration of the usable program
 */
enum class ProgramName {
    NORMAL, SKYBOX, DIRLIGHT, MULTILIGHTS, ISLAND
};

/**
 * @brief Stores necessary data to interact with a GLSL program
 */
class Program {

protected:
    // MEMBERS

    /**
     * @brief Program instance
     */
    glimac::Program _program;

    /**
     * @brief Uniform location of the Model View Projection matrix variable
     */
    GLint _uMatMVP;

    /**
     * @brief Uniform location of the Model View matrix variable
     */
    GLint _uMatMV;

    /**
     * @brief Uniform location of the Normal matrix variable
     */
    GLint _uMatNormal;

protected: // singleton
    // CONSTRUCTORS & DESTRUCTORS

    /**
     * @brief Program class constructor
     * @param vsName  Vertex shader file name without extension (assumed to be .vs.glsl)
     * @param fsName  Fragment shader file name without extension (assumed to be .fs.glsl)
     */
    Program(const std::string& vsName, const std::string& fsName)
        :_program( glimac::loadProgram(
        cfg::PATH_SHADERS + vsName + ".vs.glsl",
        cfg::PATH_SHADERS + fsName + ".fs.glsl")),
         _uMatMVP( glGetUniformLocation(_program.getGLId(), "uMatMVP") ),
         _uMatMV( glGetUniformLocation(_program.getGLId(), "uMatMV") ),
         _uMatNormal( glGetUniformLocation(_program.getGLId(), "uMatNormal") )
    {}

    /**
     * @brief Program class default destructor
     */
    ~Program() = default;

public:
    // INTERFACE

    /**
     * @brief Gets the program name
     * @return Returns the program name
     */
    virtual ProgramName name() const = 0;

    /**
     * @brief Gets the uniform location of the Model View Projection matrix
     * @return Returns the uniform location of the Model View Projection matrix
     */
    GLint uMatMVP() const { return _uMatMVP; }

    /**
     * @brief Gets the uniform location of the Model View matrix
     * @return Returns the uniform location of the Model View matrix
     */
    GLint uMatMV() const { return _uMatMV; }

    /**
     * @brief Gets the uniform location of the Normal matrix
     * @return Returns the uniform location of the Normal matrix
     */
    GLint uMatNormal() const { return _uMatNormal; }


    /**
     * @brief Changes the currently running GLSL program to this one
     */
    virtual void use() const { _program.use(); }

};

}


#endif //LIHOWAR_PROGRAM_IPROGRAM_HPP
