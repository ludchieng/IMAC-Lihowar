#ifndef LIHOWAR_DIRLIGHTPROGRAM_HPP
#define LIHOWAR_DIRLIGHTPROGRAM_HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <lihowarlib/common.hpp>
#include <lihowarlib/programs/Program.hpp>

namespace lihowar {

class DirLightProgram : public Program {

private:
    // MEMBERS
    ProgramType _type;
    GLint _uKd;
    GLint _uKs;
    GLint _uShininess;
    GLint _uLightDir;
    GLint _uLightIntensity;
    GLint _uColor;

private:
    // CONSTRUCTORS & DESTRUCTORS
    DirLightProgram(const std::string& vsName, const std::string& fsName)
       :Program(vsName, fsName),
        _type( ProgramType::DirLight ),
        _uKd( glGetUniformLocation(_program.getGLId(), "uKd") ),
        _uKs( glGetUniformLocation(_program.getGLId(), "uKs") ),
        _uShininess( glGetUniformLocation(_program.getGLId(), "uShininess") ),
        _uLightDir( glGetUniformLocation(_program.getGLId(), "uLightDir") ),
        _uLightIntensity( glGetUniformLocation(_program.getGLId(), "uLightIntensity") ),
        _uColor( glGetUniformLocation(_program.getGLId(), "uColor") )
    {
        if (DEBUG) std::cout << "[DirLightProgram::DirLightProgram] _type: " << _type << std::endl;
    }

public:
    /// \brief get instance of the Program singleton class
    static DirLightProgram& instance() {
        static DirLightProgram instance("3D", "dirlight");
        return instance;
    }

public:
    // INTERFACE
    ProgramType type() const override { return _type; }
    GLint uKd() const { return _uKd; }
    GLint uKs() const { return _uKs; }
    GLint uShininess() const { return _uShininess; }
    GLint uLightDir() const { return _uLightDir; }
    GLint uLightIntensity() const { return _uLightIntensity; }
    GLint uColor() const { return _uColor; }

};

}

#endif //LIHOWAR_DIRLIGHTPROGRAM_HPP