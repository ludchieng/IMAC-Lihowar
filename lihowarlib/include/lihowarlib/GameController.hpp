#ifndef LIHOWAR_GAMECONTROLLER_HPP
#define LIHOWAR_GAMECONTROLLER_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/AssetManager.hpp>

namespace lihowar {

class GameController {

private:
    // MEMBERS

public:
    // CONSTRUCTORS & DESTRUCTORS
    GameController() = default;
    ~GameController() = default;

public:
    // INTERFACE
    void update();
    void render();

};

}


#endif //LIHOWAR_GAMECONTROLLER_HPP
