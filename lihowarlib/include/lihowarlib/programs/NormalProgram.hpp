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
#ifndef LIHOWAR_NORMALPROGRAM_HPP
#define LIHOWAR_NORMALPROGRAM_HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/programs/Program.hpp>

namespace lihowar {

class NormalProgram : public Program {

private:
    // MEMBERS
    ProgramType _type;

private:
    // CONSTRUCTORS & DESTRUCTORS
    NormalProgram(const std::string& vsName, const std::string& fsName)
        : Program(vsName, fsName),
        _type( ProgramType::NORMAL )
    {}

public:
    /// \brief get instance of the Program singleton class
    static NormalProgram& instance() {
        static NormalProgram instance("3D", "normals");
        return instance;
    }

public:
    // INTERFACE
    ProgramType type() const override { return _type; }

};

}

#endif //LIHOWAR_NORMALPROGRAM_HPP