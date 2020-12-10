#ifndef LIHOWAR_NORMALPROGRAM_HPP
#define LIHOWAR_NORMALPROGRAM_HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <lihowarlib/common.hpp>
#include <lihowarlib/programs/Program.hpp>

namespace lihowar {

class NormalProgram : public Program {

private:
    // MEMBERS

private:
    // CONSTRUCTORS & DESTRUCTORS
    NormalProgram(const std::string& vsName, const std::string& fsName)
        : Program(vsName, fsName)
    {}

public:
    /// \brief get instance of the Program singleton class
    static NormalProgram& instance() {
        static NormalProgram instance("3D", "normals");
        return instance;
    }

public:
    // INTERFACE

};

}

#endif //LIHOWAR_NORMALPROGRAM_HPP