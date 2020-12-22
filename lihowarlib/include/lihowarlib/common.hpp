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

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;
const float ASPECT_RATIO = WINDOW_WIDTH / (float) WINDOW_HEIGHT;

const float MAX_FRAMERATE = 60.f;

const float MIN_FOV = 70.0f;
const float MAX_FOV = 95.0f;

const float Z_NEAR = .1f;
const float Z_FAR = 5000.f;

const float MASS_DENSITY = 1.f;
const float INERTIA_COEF = 1.f;
const float TORQUE_MIN_DIST = .01f;
const float LINEAR_DRAG_COEF = 10.f;
const float ANGULAR_DRAG_COEF = 5.f;
const float LINEAR_VELOCITY_SLIP_LIMIT = .005f;
const float ANGULAR_VELOCITY_SLIP_LIMIT = .0005f;

}

#endif
