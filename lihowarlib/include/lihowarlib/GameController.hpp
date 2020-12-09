#ifndef LIHOWAR_GAMECONTROLLER_HPP
#define LIHOWAR_GAMECONTROLLER_HPP

#include <lihowarlib/common.hpp>
#include <lihowarlib/AssetManager.hpp>
#include <lihowarlib/GameRenderer.hpp>

namespace lihowar {

class GameController {

private:
    // MEMBERS
    AssetManager &_assetManager;
    GameRenderer &_gRenderer;

public:
    // CONSTRUCTORS & DESTRUCTORS
    GameController()
      : _assetManager(AssetManager::instance()),
        _gRenderer(GameRenderer::instance()) {}

    ~GameController() = default;

public:
    // INTERFACE
    void update();
    void render();

};

}


#endif //LIHOWAR_GAMECONTROLLER_HPP
