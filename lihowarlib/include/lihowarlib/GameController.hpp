#ifndef LIHOWAR_GAMECONTROLLER_HPP
#define LIHOWAR_GAMECONTROLLER_HPP

#include <list>
#include <lihowarlib/GameConfig.hpp>
#include <lihowarlib/GameRenderer.hpp>
#include <lihowarlib/Scene.hpp>
#include <lihowarlib/io/SceneSerializer.hpp>


namespace lihowar {

class GameController {

private:
    // MEMBERS
    std::unique_ptr<Scene> _scene;
    GameRenderer &_gRenderer;

private:
    // CONSTRUCTORS & DESTRUCTORS
    GameController();

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
    Scene &scene() { return *_scene; }
    GameRenderer& renderer() { return _gRenderer; }

    void update();
    void render() { _gRenderer.render(*_scene); }

};

}


#endif //LIHOWAR_GAMECONTROLLER_HPP
