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
#include <lihowarlib/GameConfig.hpp>

using namespace lihowar;

namespace lihowar {

bool         GameConfig::DEBUG            = true;

std::string  GameConfig::PATH_ASSETS      ("assets/");
std::string  GameConfig::PATH_SHADERS     ("shaders/");
std::string  GameConfig::PATH_SCENES      ("scenes/");

bool         GameConfig::FULLSCREEN       = false;
unsigned int GameConfig::WINDOW_WIDTH     = (cfg::FULLSCREEN) ? 1920 : 1280;
unsigned int GameConfig::WINDOW_HEIGHT    = (cfg::FULLSCREEN) ? 1080 : 720;
float        GameConfig::ASPECT_RATIO     = cfg::WINDOW_WIDTH / (float) cfg::WINDOW_HEIGHT;

float        GameConfig::MAX_FRAMERATE    = 60.f;

float        GameConfig::MIN_FOV          = 70.0f;
float        GameConfig::MAX_FOV          = 95.0f;

float        GameConfig::Z_NEAR           = .1f;
float        GameConfig::Z_FAR            = 5000.f;

bool         GameConfig::USE_ANTIALIASING = false;
unsigned int GameConfig::MSAA             = 1*2;

std::string  GameConfig::SCENE            ("scene1.json");

}
