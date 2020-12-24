#include "glimac/SDLWindowManager.hpp"
#include <iostream>

namespace glimac {

SDLWindowManager::SDLWindowManager(
        uint32_t width,
        uint32_t height,
        const char* title,
        int initFlags,
        int windowFlags)
{
    if(0 != SDL_Init(initFlags)) {
        std::cerr << SDL_GetError() << std::endl;
        return;
    }

    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED, width, height, windowFlags);

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    if(nullptr == m_renderer) {
        std::cerr << SDL_GetError() << std::endl;
        return;
    }

    m_gl = SDL_GL_CreateContext(m_window);
}

SDLWindowManager::~SDLWindowManager() {
    SDL_GL_DeleteContext(m_gl);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool SDLWindowManager::pollEvent(SDL_Event& e) {
    return SDL_PollEvent(&e);
}

bool SDLWindowManager::isKeyPressed(SDL_Scancode scancode) const {
    return SDL_GetKeyboardState(nullptr)[scancode];
}

// button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
bool SDLWindowManager::isMouseButtonPressed(uint32_t button) const {
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
}

glm::ivec2 SDLWindowManager::getMousePosition() const {
    glm::ivec2 mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    return mousePos;
}

void SDLWindowManager::swapBuffers() {
    SDL_GL_SwapWindow(m_window);
}

float SDLWindowManager::getTime() const {
    return 0.001f * SDL_GetTicks();
}

}
