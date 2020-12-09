#ifndef LIHOWAR_CONTROLLER_HPP
#define LIHOWAR_CONTROLLER_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/AssetManager.hpp>

namespace lihowar {

class Controller {

private:
    // MEMBERS

public:
    // CONSTRUCTORS & DESTRUCTORS
    Controller() = default;
    ~Controller() = default;

public:
    // INTERFACE
    void update();
    void render();

};

}


#endif //LIHOWAR_CONTROLLER_HPP
