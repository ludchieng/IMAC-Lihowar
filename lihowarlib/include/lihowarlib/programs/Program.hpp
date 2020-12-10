#ifndef LIHOWAR_PROGRAM_IPROGRAM_HPP
#define LIHOWAR_PROGRAM_IPROGRAM_HPP

#include <glimac/Program.hpp>
#include <lihowarlib/common.hpp>

namespace lihowar {

class Program {
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
        PATH_SHADERS + vsName + ".vs.glsl",
        PATH_SHADERS + fsName + ".fs.glsl")),
         _uMatMVP( glGetUniformLocation(_program.getGLId(), "uMatMVP") ),
         _uMatMV( glGetUniformLocation(_program.getGLId(), "uMatMV") ),
         _uMatNormal( glGetUniformLocation(_program.getGLId(), "uMatNormal") )
    {}

    ~Program() = default;

public:
    /// \brief get instance of the Program singleton class
    static Program& instance(const std::string& vsName, const std::string& fsName) {
        static Program instance(vsName, fsName);
        return instance;
    }
    // prevent instance duplication
    Program(const Program&) = delete;
    Program(Program&&) = delete;
    Program& operator=(const Program&) = delete;
    Program& operator=(Program&&) = delete;

public:
    // INTERFACE
    GLint uMatMVP() const { return _uMatMVP; }
    GLint uMatMV() const { return _uMatMV; }
    GLint uMatNormal() const { return _uMatNormal; }

    void use() { _program.use(); }

};

}


#endif //LIHOWAR_PROGRAM_IPROGRAM_HPP
