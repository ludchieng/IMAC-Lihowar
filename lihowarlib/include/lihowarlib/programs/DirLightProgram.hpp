#ifndef LIHOWAR_DIRLIGHTPROGRAM_HPP
#define LIHOWAR_DIRLIGHTPROGRAM_HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/programs/Program.hpp>

namespace lihowar {

class DirLightProgram : public Program {

private:
    // MEMBERS
    ProgramType _type;
    GLint _uKd;
    GLint _uKs;
    GLint _uKa;
    GLint _uShininess;
    GLint _uLightDir;
    GLint _uLightIntensity;
    GLint _uHasTexture;

private:
    // CONSTRUCTORS & DESTRUCTORS
    DirLightProgram(const std::string& vsName, const std::string& fsName)
       :Program(vsName, fsName),
        _type( ProgramType::DIRLIGHT ),
        _uKd( glGetUniformLocation(_program.getGLId(), "uKd") ),
        _uKs( glGetUniformLocation(_program.getGLId(), "uKs") ),
        _uKa( glGetUniformLocation(_program.getGLId(), "uKa") ),
        _uShininess( glGetUniformLocation(_program.getGLId(), "uShininess") ),
        _uLightDir( glGetUniformLocation(_program.getGLId(), "uLightDir") ),
        _uLightIntensity( glGetUniformLocation(_program.getGLId(), "uLightIntensity") ),
        _uHasTexture( glGetUniformLocation(_program.getGLId(), "uHasTexture") )
    {}

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
    GLint uKa() const { return _uKa; }
    GLint uShininess() const { return _uShininess; }
    GLint uLightDir() const { return _uLightDir; }
    GLint uLightIntensity() const { return _uLightIntensity; }
    GLint uHasTexture() const { return _uHasTexture; }

};

}

#endif //LIHOWAR_DIRLIGHTPROGRAM_HPP