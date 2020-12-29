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
#ifndef LIHOWAR_ISLANDPROGRAM_HPP
#define LIHOWAR_ISLANDPROGRAM_HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/programs/Program.hpp>
#include <lihowarlib/exceptions/LihowarException.hpp>

namespace lihowar {

class IslandProgram : public Program {

public:
    static const unsigned int MAX_LIGHTSDIR_COUNT = 4;    // must be the same in the f shader
    static const unsigned int MAX_LIGHTSPOINT_COUNT = 12; // must be the same in the f shader

private:
    // MEMBERS
    ProgramType _type;
    GLint _uKd;
    GLint _uKs;
    GLint _uShininess;
    GLint _uLightAmbient;
    GLint _uLightsDirCount;
    GLint _uLightsPointCount;

private:
    // CONSTRUCTORS & DESTRUCTORS
    IslandProgram(const std::string& vsName, const std::string& fsName)
       : Program(vsName, fsName),
         _type( ProgramType::ISLAND ),
         _uKd( glGetUniformLocation(_program.getGLId(), "uKd") ),
         _uKs( glGetUniformLocation(_program.getGLId(), "uKs") ),
         _uShininess( glGetUniformLocation(_program.getGLId(), "uShininess") ),
         _uLightAmbient( glGetUniformLocation(_program.getGLId(), "uLightAmbient") ),
         _uLightsDirCount( glGetUniformLocation(_program.getGLId(), "uLightsDirCount") ),
         _uLightsPointCount( glGetUniformLocation(_program.getGLId(), "uLightsPointCount") )
    {}

public:
    /// \brief get instance of the Program singleton class
    static IslandProgram& instance() {
        static IslandProgram instance("island", "island");
        return instance;
    }

public:
    // INTERFACE
    ProgramType type() const override { return _type; }
    GLint uKd() const { return _uKd; }
    GLint uKs() const { return _uKs; }
    GLint uShininess() const { return _uShininess; }
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

#endif //LIHOWAR_ISLANDPROGRAM_HPP
