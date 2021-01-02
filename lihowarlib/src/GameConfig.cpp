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

std::string  cfg::EXEC_PATH        ("");
std::string  cfg::EXEC_DIR         ("");

// These are hard coded default config
// (last fallback if any of the json files have failed)
bool         cfg::DEBUG            = false;

std::string  cfg::PATH_ASSETS      ("assets/");
std::string  cfg::PATH_SHADERS     ("shaders/");
std::string  cfg::PATH_SCENES      ("scenes/");

bool         cfg::FULLSCREEN       = false;
unsigned int cfg::WINDOW_WIDTH     = (cfg::FULLSCREEN) ? 1920 : 1600;
unsigned int cfg::WINDOW_HEIGHT    = (cfg::FULLSCREEN) ? 1080 : 900;
float        cfg::ASPECT_RATIO     = cfg::WINDOW_WIDTH / (float) cfg::WINDOW_HEIGHT;

float        cfg::MAX_FRAMERATE    = 60.f;

float        cfg::MIN_FOV          = 70.0f;
float        cfg::MAX_FOV          = 95.0f;

float        cfg::Z_NEAR           = .1f;
float        cfg::Z_FAR            = 5000.f;

bool         cfg::USE_ANTIALIASING = true;
unsigned int cfg::MSAA             = 1*2;

std::string  cfg::SCENE            ("scene1.json");

}
