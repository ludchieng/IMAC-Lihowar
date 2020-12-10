#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <lihowarlib/common.hpp>
#include <lihowarlib/Game.hpp>
#include <iostream>
#include <cstddef>
#include <vector>

const float MAX_FRAMERATE = 60.f;

int main(int argc, char** argv) {
    // Init SDL Window
    glimac::SDLWindowManager wm(
            lihowar::WINDOW_WIDTH,
            lihowar::WINDOW_HEIGHT,
            "Lihowar");

    // Init GLEW
    if (GLEW_OK != glewInit()) {
        std::cerr << "Could not init GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Init Game
    lihowar::Game &game = lihowar::Game::instance(wm);

    // Game loop
    while(game.isRunning()) {
        Uint32 startTime = SDL_GetTicks();

        // Event loop:
        SDL_Event e;
        while(wm.pollEvent(e)) {
            game.handle(e);
        }

        game.render();
        wm.swapBuffers();

        // Limit framerate
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if (elapsedTime < 1000. / MAX_FRAMERATE) {
            SDL_Delay(1000. / MAX_FRAMERATE - elapsedTime);
        }
    }

    return EXIT_SUCCESS;
}