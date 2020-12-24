#pragma once

#include <cstdint>
#include <SDL2/SDL.h>
#include "glm.hpp"

namespace glimac {

class SDLWindowManager {
public:
    SDLWindowManager(
            uint32_t width,
            uint32_t height,
            const char* title,
            int initFlags = SDL_INIT_VIDEO,
            int windowFlags = SDL_WINDOW_OPENGL,
            unsigned int msaaSamples = 1);

    ~SDLWindowManager();

    bool pollEvent(SDL_Event& e);

    bool isKeyPressed(SDL_Scancode scancode) const;

    template<typename... Args>
    bool isKeyPressed(SDL_Scancode scancode, Args... args) const {
        return SDL_GetKeyboardState(nullptr)[scancode]
               || isKeyPressed(args...);
    }
    // button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
    bool isMouseButtonPressed(uint32_t button) const;

    glm::ivec2 getMousePosition() const;

    void swapBuffers();

    // Return the time in seconds
    float getTime() const;

    SDL_Window &get() { return *m_window; }
    SDL_Renderer &getRenderer() { return *m_renderer; }
    SDL_GLContext &getGLContext() { return m_gl; }

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_GLContext m_gl;
};

}
