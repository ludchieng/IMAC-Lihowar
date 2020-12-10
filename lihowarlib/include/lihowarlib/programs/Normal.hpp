#ifndef LIHOWAR_PROGRAM_NORMAL_HPP
#define LIHOWAR_PROGRAM_NORMAL_HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <lihowarlib/common.hpp>

namespace lihowar {

namespace program {

class Normal {

private:
    // MEMBERS
    glimac::Program _program;
    GLint _uMatMVP;
    GLint _uMatMV;
    GLint _uMatNormal;

private:
    // CONSTRUCTORS & DESTRUCTORS
    Normal()
       :_program( glimac::loadProgram(
            PATH_SHADERS + "3D" + ".vs.glsl",
            PATH_SHADERS + "normals" + ".fs.glsl")),
        _uMatMVP( glGetUniformLocation(_program.getGLId(), "uMatMVP") ),
        _uMatMV( glGetUniformLocation(_program.getGLId(), "uMatMV") ),
        _uMatNormal( glGetUniformLocation(_program.getGLId(), "uMatNormal") )
    {}

public:
    /// \brief get instance of the Normal singleton class
    static Normal& instance() {
        static Normal instance;
        return instance;
    }
    // prevent instance duplication
    Normal(const Normal&) = delete;
    Normal(Normal&&) = delete;
    Normal& operator=(const Normal&) = delete;
    Normal& operator=(Normal&&) = delete;

public:
    // INTERFACE
    GLint uMatMVP() const { return _uMatMVP; }
    GLint uMatMV() const { return _uMatMV; }
    GLint uMatNormal() const { return _uMatNormal; }

    void use() { _program.use(); }

};

}

}

#endif //LIHOWAR_PROGRAM_NORMAL_HPP