#ifndef __COMMON__HPP
#define __COMMON__HPP

#include <glimac/glm.hpp>
#include <string>
#include <iostream>

namespace lihowar {

const bool DEBUG = true;

const std::string PATH_ASSETS("assets/");
const std::string PATH_SHADERS("shaders/");
const std::string PATH_SCENES("scenes/");

const bool FULLSCREEN = false;
const unsigned int WINDOW_WIDTH = (FULLSCREEN) ? 1920 : 1280;
const unsigned int WINDOW_HEIGHT = (FULLSCREEN) ? 1080 : 720;
const float ASPECT_RATIO = WINDOW_WIDTH / (float) WINDOW_HEIGHT;

const float MAX_FRAMERATE = 60.f;

const float MIN_FOV = 70.0f;
const float MAX_FOV = 95.0f;

const float Z_NEAR = .1f;
const float Z_FAR = 5000.f;

const bool USE_ANTIALIASING = false;
const unsigned int MSAA = 1*2;

const float MASS_DENSITY = 1.f;
const float INERTIA_COEF = 1.f;
const float TORQUE_MIN_DIST = .01f;
const float LINEAR_DRAG_COEF = 20.f;
const float ANGULAR_DRAG_COEF = 20.f;
const float LINEAR_VELOCITY_SLIP_LIMIT = .0002f;
const float ANGULAR_VELOCITY_SLIP_LIMIT = .000004f;

}

#endif
