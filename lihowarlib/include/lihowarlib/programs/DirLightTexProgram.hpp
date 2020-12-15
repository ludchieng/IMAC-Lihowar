#ifndef LIHOWAR_DIRLIGHTTEXPROGRAM_HPP
#define LIHOWAR_DIRLIGHTTEXPROGRAM_HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <lihowarlib/common.hpp>
#include <lihowarlib/programs/Program.hpp>

namespace lihowar {

class DirLightTexProgram : public Program {

private:
    // MEMBERS
    ProgramType _type;
    GLint _uKd;
    GLint _uKs;
    GLint _uShininess;
    GLint _uLightDir;
    GLint _uLightIntensity;
    GLint _uColor;
    GLint _uTexture;

private:
    // CONSTRUCTORS & DESTRUCTORS
    DirLightTexProgram(const std::string& vsName, const std::string& fsName)
       :Program(vsName, fsName),
        _type( ProgramType::DirLightTex ),
        _uKd( glGetUniformLocation(_program.getGLId(), "uKd") ),
        _uKs( glGetUniformLocation(_program.getGLId(), "uKs") ),
        _uShininess( glGetUniformLocation(_program.getGLId(), "uShininess") ),
        _uLightDir( glGetUniformLocation(_program.getGLId(), "uLightDir") ),
        _uLightIntensity( glGetUniformLocation(_program.getGLId(), "uLightIntensity") ),
        _uColor( glGetUniformLocation(_program.getGLId(), "uColor") ),
        _uTexture( glGetUniformLocation(_program.getGLId(), "uTexture") )
    {}

public:
    /// \brief get instance of the Program singleton class
    static DirLightTexProgram& instance() {
        static DirLightTexProgram instance("3D", "dirlighttex");
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
    GLint uTexture() const { return _uTexture; }

    void use() override {
        glUniform1i(_uTexture, 0);
        _program.use();
    }

};

}

#endif //LIHOWAR_DIRLIGHTTEXPROGRAM_HPP