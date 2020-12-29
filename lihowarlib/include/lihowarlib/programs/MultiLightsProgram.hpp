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
#ifndef LIHOWAR_MULTILIGHTSPROGRAM_HPP
#define LIHOWAR_MULTILIGHTSPROGRAM_HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <lihowarlib/GameConfig.hpp>
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
    GLint _uKl;
    GLint _uKao;
    GLint _uKn;
    GLint _uShininess;
    GLint _uHasDiffuseMap;
    GLint _uHasSpecularMap;
    GLint _uHasLuminMap;
    GLint _uHasAOMap;
    GLint _uHasNormalMap;
    GLint _uDiffuseMap;
    GLint _uSpecularMap;
    GLint _uLuminMap;
    GLint _uAOMap;
    GLint _uNormalMap;
    GLint _uLightAmbient;
    GLint _uLightsDirCount;
    GLint _uLightsPointCount;

private:
    // CONSTRUCTORS & DESTRUCTORS
    MultiLightsProgram(const std::string& vsName, const std::string& fsName)
       : Program(vsName, fsName),
         _type( ProgramType::MULTILIGHTS ),
         _uKd( glGetUniformLocation(_program.getGLId(), "uKd") ),
         _uKs( glGetUniformLocation(_program.getGLId(), "uKs") ),
         _uKl( glGetUniformLocation(_program.getGLId(), "uKl") ),
         _uKao( glGetUniformLocation(_program.getGLId(), "uKao") ),
         _uKn( glGetUniformLocation(_program.getGLId(), "uKn") ),
         _uShininess( glGetUniformLocation(_program.getGLId(), "uShininess") ),
         _uHasDiffuseMap( glGetUniformLocation(_program.getGLId(), "uHasDiffuseMap") ),
         _uHasSpecularMap( glGetUniformLocation(_program.getGLId(), "uHasSpecularMap") ),
         _uHasLuminMap( glGetUniformLocation(_program.getGLId(), "uHasLuminMap") ),
         _uHasAOMap( glGetUniformLocation(_program.getGLId(), "uHasAOMap") ),
         _uHasNormalMap( glGetUniformLocation(_program.getGLId(), "uHasNormalMap") ),
         _uDiffuseMap( glGetUniformLocation(_program.getGLId(), "uDiffuseMap") ),
         _uSpecularMap( glGetUniformLocation(_program.getGLId(), "uSpecularMap") ),
         _uLuminMap( glGetUniformLocation(_program.getGLId(), "uLuminMap") ),
         _uAOMap( glGetUniformLocation(_program.getGLId(), "uAOMap") ),
         _uNormalMap( glGetUniformLocation(_program.getGLId(), "uNormalMap") ),
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
    GLint uKl() const { return _uKl; }
    GLint uKao() const { return _uKao; }
    GLint uKn() const { return _uKn; }
    GLint uShininess() const { return _uShininess; }
    GLint uHasDiffuseMap() const { return _uHasDiffuseMap; }
    GLint uHasSpecularMap() const { return _uHasSpecularMap; }
    GLint uHasLuminMap() const { return _uHasLuminMap; }
    GLint uHasAOMap() const { return _uHasAOMap; }
    GLint uHasNormalMap() const { return _uHasNormalMap; }
    GLint uDiffuseMap() const { return _uDiffuseMap; }
    GLint uSpecularMap() const { return _uSpecularMap; }
    GLint uLuminMap() const { return _uLuminMap; }
    GLint uAOMap() const { return _uAOMap; }
    GLint uNormalMap() const { return _uNormalMap; }
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