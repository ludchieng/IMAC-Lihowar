#ifndef LIHOWAR_SKYBOXPROGRAM_HPP
#define LIHOWAR_SKYBOXPROGRAM_HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/programs/Program.hpp>

namespace lihowar {

class SkyboxProgram : public Program {

private:
    // MEMBERS
    ProgramType _type;

private:
    // CONSTRUCTORS & DESTRUCTORS
    SkyboxProgram(const std::string& vsName, const std::string& fsName)
        : Program(vsName, fsName),
        _type( ProgramType::SKYBOX )
    {}

public:
    /// \brief get instance of the Program singleton class
    static SkyboxProgram& instance() {
        static SkyboxProgram instance("skybox", "skybox");
        return instance;
    }

public:
    // INTERFACE
    ProgramType type() const override { return _type; }

};

}

#endif //LIHOWAR_SKYBOXPROGRAM_HPP