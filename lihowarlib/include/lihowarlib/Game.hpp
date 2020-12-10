#ifndef LIHOWAR_GAME_HPP
#define LIHOWAR_GAME_HPP

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <lihowarlib/common.hpp>
#include <lihowarlib/GameController.hpp>

using namespace lihowar;

namespace lihowar {

class Game {

private:
    // MEMBERS
    bool _isRunning = true;
    GameController &_gController;
    glimac::SDLWindowManager &_windowManager;

private:
    // CONSTRUCTORS & DESTRUCTORS
    explicit Game(glimac::SDLWindowManager &wm)
       :_gController(GameController::instance()),
        _windowManager(wm) {}

    ~Game() = default;

public:
    /// \brief get instance of the Game singleton class
    static Game& instance(glimac::SDLWindowManager &wm) {
        static Game instance(wm);
        return instance;
    }
    // prevent instance duplication
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

public:
    // INTERFACE
    bool isRunning() const { return _isRunning; }

    void update() { _gController.update(); };
    void render() { _gController.render(); };
    void handle(SDL_Event event);
    void handleKeydown(SDL_Event event);
    void handleMouseBtn(SDL_Event event);
    void handleMouseMotion(SDL_Event event);

};

}


#endif //LIHOWAR_GAME_HPP
