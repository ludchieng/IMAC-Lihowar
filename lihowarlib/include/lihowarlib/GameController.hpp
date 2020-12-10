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

private:
    // CONSTRUCTORS & DESTRUCTORS
    GameController()
      : _assetManager(AssetManager::instance()),
        _gRenderer(GameRenderer::instance()) {}

    ~GameController() = default;

public:
    /// \brief get instance of the GameController singleton class
    static GameController& instance() {
        static GameController instance;
        return instance;
    }
    // prevent instance duplication
    GameController(const GameController&) = delete;
    GameController(GameController&&) = delete;
    GameController& operator=(const GameController&) = delete;
    GameController& operator=(GameController&&) = delete;

public:
    // INTERFACE
    GameRenderer& renderer() { return _gRenderer; }

    void update();
    void render();

};

}


#endif //LIHOWAR_GAMECONTROLLER_HPP
