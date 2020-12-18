#ifndef LIHOWAR_MULTILIGHTSPROGRAM_HPP
#define LIHOWAR_MULTILIGHTSPROGRAM_HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <lihowarlib/common.hpp>
#include <lihowarlib/programs/Program.hpp>
#include <lihowarlib/exceptions/LihowarException.hpp>

namespace lihowar {

class MultiLightsProgram : public Program {

public:
    static const unsigned int MAX_LIGHTSDIR_COUNT = 4; // must be the same in the f shader
    static const unsigned int MAX_LIGHTSPOINT_COUNT = 12; // must be the same in the f shader

private:
    // MEMBERS
    ProgramType _type;
    GLint _uKd;
    GLint _uKs;
    GLint _uShininess;
    GLint _uHasTexture;
    GLint _uLightAmbient;
    GLint _uLightsDirCount;
    GLint _uLightsPointCount;

private:
    // CONSTRUCTORS & DESTRUCTORS
    MultiLightsProgram(const std::string& vsName, const std::string& fsName)
       :Program(vsName, fsName),
        _type( ProgramType::MULTILIGHTS ),
        _uKd( glGetUniformLocation(_program.getGLId(), "uKd") ),
        _uKs( glGetUniformLocation(_program.getGLId(), "uKs") ),
        _uShininess( glGetUniformLocation(_program.getGLId(), "uShininess") ),
        _uHasTexture( glGetUniformLocation(_program.getGLId(), "uHasTexture") ),
        _uLightAmbient( glGetUniformLocation(_program.getGLId(), "uLightAmbient") ),
        _uLightsDirCount( glGetUniformLocation(_program.getGLId(), "uLightsDirCount") ),
        _uLightsPointCount( glGetUniformLocation(_program.getGLId(), "uLightsPointCount") )
    {}

public:
    /// \brief get instance of the Program singleton class
    static MultiLightsProgram& instance() {
        static MultiLightsProgram instance("3D", "multilights");
        return instance;
    }

public:
    // INTERFACE
    ProgramType type() const override { return _type; }
    GLint uKd() const { return _uKd; }
    GLint uKs() const { return _uKs; }
    GLint uShininess() const { return _uShininess; }
    GLint uHasTexture() const { return _uHasTexture; }
    GLint uLightAmbient() const { return _uLightAmbient; }
    GLint uLightsDirCount() const { return _uLightsDirCount; }
    GLint uLightsPointCount() const { return _uLightsPointCount; }

    GLint uLightsDir(unsigned int index, std::string attr) const {
        if (index >= MAX_LIGHTSDIR_COUNT)
            throw LihowarException("Trying to access memory out of array bound", __FILE__, __LINE__);

        std::string varname("uLightsDir[" + std::to_string(index) + "]." + attr);
        return glGetUniformLocation(_program.getGLId(), varname.c_str());
    }
    GLint uLightsPoint(unsigned int index, std::string attr) const {
        if (index >= MAX_LIGHTSPOINT_COUNT)
            throw LihowarException("Trying to access memory out of array bound", __FILE__, __LINE__);

        std::string varname("uLightsPoint[" + std::to_string(index) + "]." + attr);
        return glGetUniformLocation(_program.getGLId(), varname.c_str());
    }


};

}

#endif //LIHOWAR_MULTILIGHTSPROGRAM_HPP