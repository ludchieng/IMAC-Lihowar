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
/*#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <lihowarlib/Game.hpp>
#include <lihowarlib/GameConfig.hpp>*/
#include <iostream>


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return -1;
    // Initialisation de SDL_Mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation SDL_mixer : %s", Mix_GetError());
        SDL_Quit();
        return -1;
    }

    Mix_Chunk * audio = Mix_LoadWAV_RW(SDL_RWFromFile("assets/sounds/lihowar.wav", "rb"), 1);

    if (audio == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

    Mix_PlayChannel(-1, audio, -1);
    std::cout << Mix_GetError() << std::endl;
    Mix_VolumeMusic(MIX_MAX_VOLUME);

    SDL_Window* pWindow = nullptr;
    SDL_Renderer* pRenderer = nullptr;
    SDL_Event events;
    bool close = false;

    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer);

    while (!close)
    {
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_WINDOWEVENT && events.window.event == SDL_WINDOWEVENT_CLOSE)
                close = true;
        }

        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(pRenderer);
        SDL_RenderPresent(pRenderer);
    }

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    Mix_FreeChunk(audio); // Libére en mémoire notre musique
    Mix_CloseAudio(); // Quitter correctement SDL_Mixer
    SDL_Quit();

    return 0;
}



/*

int main(int argc, char** argv)
{
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
*/