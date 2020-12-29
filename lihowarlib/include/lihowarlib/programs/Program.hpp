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

enum class ProgramType {
    NORMAL, SKYBOX, DIRLIGHT, MULTILIGHTS, ISLAND
};

class Program {
    friend class SceneSerializer;

protected:
    // MEMBERS
    glimac::Program _program;
    GLint _uMatMVP;
    GLint _uMatMV;
    GLint _uMatNormal;

protected:
    // CONSTRUCTORS & DESTRUCTORS
    Program(const std::string& vsName, const std::string& fsName)
        :_program( glimac::loadProgram(
        cfg::PATH_SHADERS + vsName + ".vs.glsl",
        cfg::PATH_SHADERS + fsName + ".fs.glsl")),
         _uMatMVP( glGetUniformLocation(_program.getGLId(), "uMatMVP") ),
         _uMatMV( glGetUniformLocation(_program.getGLId(), "uMatMV") ),
         _uMatNormal( glGetUniformLocation(_program.getGLId(), "uMatNormal") )
    {}

    ~Program() = default;

public:
    // INTERFACE
    virtual ProgramType type() const = 0;
    GLint uMatMVP() const { return _uMatMVP; }
    GLint uMatMV() const { return _uMatMV; }
    GLint uMatNormal() const { return _uMatNormal; }

    virtual void use() const { _program.use(); }

};

}


#endif //LIHOWAR_PROGRAM_IPROGRAM_HPP
