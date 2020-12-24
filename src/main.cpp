#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <lihowarlib/common.hpp>
#include <lihowarlib/Game.hpp>
#include <iostream>

int main(int argc, char** argv) {
    // Init SDL Window
    glimac::SDLWindowManager wm(
            lihowar::WINDOW_WIDTH,
            lihowar::WINDOW_HEIGHT,
            "Lihowar",
            SDL_INIT_VIDEO | SDL_INIT_JOYSTICK,
            SDL_WINDOW_OPENGL);

    // Init GLEW
    if (GLEW_OK != glewInit()) {
        std::cerr << "Could not init GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Init Game
    lihowar::Game &game = lihowar::Game::instance(wm);

    int cnt = 0;
    int time = 0;

    // Game loop
    while(game.isRunning()) {
        Uint32 startTime = SDL_GetTicks();

        // Event loop:
        SDL_Event e;
        while(wm.pollEvent(e)) {
            game.handle(e);
        }

        game.update();
        game.render();
        wm.swapBuffers();

        // Limit framerate
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /*time += elapsedTime;
        if (++cnt % 50 == 0) {
            std::cout << 1000 / (time / 50) << " fps" << std::endl;
            time = 0;
        }*/
        if (elapsedTime < 1000. / lihowar::MAX_FRAMERATE) {
            SDL_Delay(1000. / lihowar::MAX_FRAMERATE - elapsedTime);
        }
    }

    return EXIT_SUCCESS;
}