#ifndef LIHOWAR_GAME_HPP
#define LIHOWAR_GAME_HPP

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <lihowarlib/common.hpp>

namespace lihowar {

class Game {

private:
    // MEMBERS
    bool _isRunning = true;

private:
    // CONSTRUCTORS & DESTRUCTORS
    Game() = default;
    ~Game() = default;

public:
    /// \brief get instance of the WindowManager singleton class
    static Game& instance() {
        static Game instance;
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
    static void render();
    void handle(SDL_Event event);
    void handleKeydown(SDL_Event event);

};

}


#endif //LIHOWAR_GAME_HPP
