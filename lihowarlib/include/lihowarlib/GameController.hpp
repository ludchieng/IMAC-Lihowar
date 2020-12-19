#ifndef LIHOWAR_GAMECONTROLLER_HPP
#define LIHOWAR_GAMECONTROLLER_HPP

#include <list>
#include <lihowarlib/common.hpp>
#include <lihowarlib/AssetManager.hpp>
#include <lihowarlib/GameRenderer.hpp>
#include <lihowarlib/Scene.hpp>
#include <lihowarlib/io/SceneSerializer.hpp>


namespace lihowar {

class GameController {

private:
    // MEMBERS
    std::unique_ptr<Scene> _scene;
    AssetManager &_assetManager;
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
    GameRenderer& renderer() { return _gRenderer; }

    void update();
    void render();

private:
    void render(
            const std::list< std::unique_ptr<Object> > &objectsList,
            const glm::mat4 &matModelParent = glm::mat4(1.));

    void render(
            const Object &object,
            const glm::mat4 &matModelParent = glm::mat4(1.));

    void render(
            const Object *object,
            const glm::mat4 &matModelParent = glm::mat4(1.))
    {
        render(*object, matModelParent);
    }

};

}


#endif //LIHOWAR_GAMECONTROLLER_HPP
