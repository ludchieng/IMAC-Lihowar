#ifndef __COMMON__HPP
#define __COMMON__HPP

#include <glimac/glm.hpp>
#include <string>
#include <iostream>

namespace lihowar {

const bool DEBUG = true;

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;
const float ASPECT_RATIO = WINDOW_WIDTH / (float) WINDOW_HEIGHT;

const float MAX_FRAMERATE = 60.f;

const float FOV = 70.0f;

const float Z_NEAR = .1f;
const float Z_FAR = 100.f;

const std::string PATH_ASSETS("assets/");
const std::string PATH_SHADERS("shaders/");
const std::string PATH_SCENES("scenes/");

}

#endif
