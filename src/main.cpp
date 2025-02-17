/*
 *  Copyright (c) 2020-2021 Lihowar
 *
 *  This software is licensed under OSEF License.
 *
 *  The "Software" is defined as the pieces of code, the documentation files, the config
 *  files, the textures assets, the Wavefront OBJ assets, the screenshot image, the sound
 *  effects and music associated with.
 *
 *  This Software is licensed under OSEF License which means IN ACCORDANCE WITH THE LICENSE
 *  OF THE DEPENDENCIES OF THE SOFTWARE, you can use it as you want for any purpose, but
 *  it comes with no guarantee of any kind, provided that you respects the license of the
 *  software dependencies of the piece of code you want to reuse. The dependencies are
 *  listed at the end of the README given in the directory root of the Lihowar repository.
 */
#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <lihowarlib/Game.hpp>
#include <lihowarlib/GameConfig.hpp>
#include <iostream>

int main(int argc, char** argv) {
    // Load config file
    lihowar::GameConfig::load(argc, argv);

    // Init SDL Window
    glimac::SDLWindowManager wm(
            lihowar::cfg::WINDOW_WIDTH,
            lihowar::cfg::WINDOW_HEIGHT,
            "Lihowar",
            SDL_INIT_VIDEO | SDL_INIT_JOYSTICK,
            (lihowar::cfg::FULLSCREEN) ? SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN : SDL_WINDOW_OPENGL,
            (lihowar::cfg::USE_ANTIALIASING) ? lihowar::cfg::MSAA : 1);

    // Init GLEW
    if (GLEW_OK != glewInit()) {
        std::cerr << "[main] Could not init GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Init Game
    lihowar::Game &game = lihowar::Game::instance(wm);

    // Game loop
    if (cfg::DEBUG) std::cout << "[main] GAME LOOP START" << std::endl;
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
        if (elapsedTime < 1000. / lihowar::cfg::MAX_FRAMERATE) {
            SDL_Delay(1000. / lihowar::cfg::MAX_FRAMERATE - elapsedTime);
        }
    }
    if (cfg::DEBUG) std::cout << "[main] GAME LOOP END" << std::endl;

    return EXIT_SUCCESS;
}
